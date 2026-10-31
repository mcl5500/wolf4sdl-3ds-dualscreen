#!/usr/bin/env bash
set -e

IP="${1:-192.168.178.59}"
HDR="X-Requested-With: 3dsDL"
DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

echo "=== Connecting to 3DS at $IP ==="
STATUS=$(curl -s --connect-timeout 8 --max-time 15 -H "$HDR" "http://$IP/api/status" || true)
if [ -z "$STATUS" ]; then
    echo "Error: 3DS not reachable at http://$IP. Make sure 3dsDL is running!"
    exit 1
fi

ACCESS=$(echo "$STATUS" | jq -r '.access // empty' 2>/dev/null || true)
if [ "$ACCESS" != "allowed" ]; then
    echo "Requesting access on 3DS screen... Please tap 'Allow' on your 3DS!"
    curl -s -H "$HDR" "http://$IP/api/list?path=%2Fcias" >/dev/null || true
    while true; do
        STATUS=$(curl -s -H "$HDR" "http://$IP/api/status")
        ACCESS=$(echo "$STATUS" | jq -r '.access // empty' 2>/dev/null || true)
        if [ "$ACCESS" = "allowed" ]; then
            echo "Access granted! Starting transfer..."
            break
        fi
        sleep 1
    done
fi

# Ensure folders exist
curl -s -X POST -H "$HDR" -d "path=/3ds/wolf4sdl" "http://$IP/api/folder" >/dev/null || true
curl -s -X POST -H "$HDR" -d "path=/cias" "http://$IP/api/folder" >/dev/null || true

# 1. Upload .3dsx and .smdh to /3ds/wolf4sdl/
if [ -f "$DIR/wolf4sdl.3dsx" ]; then
    echo "--> Uploading wolf4sdl.3dsx to /3ds/wolf4sdl/wolf4sdl.3dsx..."
    curl -s -X PUT -H "$HDR" \
      --data-binary @"$DIR/wolf4sdl.3dsx" \
      "http://$IP/api/file?path=%2F3ds%2Fwolf4sdl%2Fwolf4sdl.3dsx&replace=1" >/dev/null
    echo "    Upload complete!"
fi

if [ -f "$DIR/wolf4sdl.smdh" ]; then
    echo "--> Uploading wolf4sdl.smdh to /3ds/wolf4sdl/wolf4sdl.smdh..."
    curl -s -X PUT -H "$HDR" \
      --data-binary @"$DIR/wolf4sdl.smdh" \
      "http://$IP/api/file?path=%2F3ds%2Fwolf4sdl%2Fwolf4sdl.smdh&replace=1" >/dev/null
    echo "    Upload complete!"
fi

# 2. Upload and install CIA
if [ -f "$DIR/Wolfenstein-3D-DualScreen.cia" ]; then
    echo "--> Uploading Wolfenstein-3D-DualScreen.cia to /cias/..."
    curl -s -X PUT -H "$HDR" \
      --data-binary @"$DIR/Wolfenstein-3D-DualScreen.cia" \
      "http://$IP/api/file?path=%2Fcias%2FWolfenstein-3D-DualScreen.cia&replace=1" >/dev/null
    echo "    Upload complete!"

    echo "--> Triggering CIA install on 3DS..."
    curl -s -X POST -H "$HDR" \
      -d "paths=/cias/Wolfenstein-3D-DualScreen.cia" \
      "http://$IP/api/install" >/dev/null
    echo "    Installation command sent to 3DS!"
fi

echo "=== Deployment finished successfully! ==="
