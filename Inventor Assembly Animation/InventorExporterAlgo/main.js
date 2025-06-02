const { exec } = require('child_process');

exec('dotnet run "data/scissors.iam" "data/assembly_json2.json"', (error, stdout, stderr) => {
  if (error) {
    console.error(`exec error: ${error.message}`);
    return;
  }
  if (stderr) {
    console.error(`stderr: ${stderr}`);
  }
  console.log(`stdout: ${stdout}`);
});
