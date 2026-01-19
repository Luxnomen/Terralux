// Calculate where the player is looking (Target)
        Vector3 lookTarget = Vector3Add(player.transform.pos, (Vector3){
            sinf(player.transform.yaw * DEG2RAD),
            tanf(player.transform.pitch * DEG2RAD),
            cosf(player.transform.yaw * DEG2RAD)
        });

        // LOCK THE CAMERA TO THE PLAYER
        Camera3D camera = { 0 };
        camera.position = player.transform.pos; // Camera is NOW INSIDE the player
        camera.target = lookTarget;             // Camera looks where player looks
        camera.up = (Vector3){0, 1, 0};
        camera.fovy = 70.0f;
        camera.projection = CAMERA_PERSPECTIVE;
