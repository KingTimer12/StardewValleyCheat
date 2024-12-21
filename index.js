const { exec } = require('node:child_process');

exec('powershell.exe -File ./build.ps1', (error, stdout, stderr) => {
    if (error) {
        console.error(`Error executing script: ${error.message}`);
        return;
    }

    if (stderr) {
        console.error(`Script error: ${stderr}`);
        return;
    }

    console.log(`Script output: ${stdout}`);
});