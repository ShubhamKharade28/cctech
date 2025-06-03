const { exec } = require('child_process');

exec('dotnet run "input-assemblies/single-cylinder/Assembly1.iam" "outputs/single_cylinder_assembly_data.json"', (error, stdout, stderr) => {
  if (error) {
    console.error(`exec error: ${error.message}`);
    return;
  }
  if (stderr) {
    console.error(`stderr: ${stderr}`);
  }
  console.log(`stdout: ${stdout}`);
});
