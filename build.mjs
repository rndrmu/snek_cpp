import { readdirSync } from 'fs';
import { exec } from 'child_process';

const sourceDir = 'src';
const buildDir = 'build';

// read the source directory and its subdirectories
const subdirectories = readdirSync(sourceDir, { withFileTypes: true })
    .filter(dirent => dirent.isDirectory());

// get all files in the source directory 
const files = readdirSync(sourceDir)
    .filter(file => file.endsWith('.cpp'));

const subdirectoryFiles = subdirectories.map(subdirectory => {
    return readdirSync(`${sourceDir}/${subdirectory.name}`)
    .filter(file => file.endsWith('.cpp') )
    .map(file => file.replace(/\/src\//, ''))
    // prepend dirnames to each file
    .map(file => `${sourceDir}/${subdirectory.name}/${file}`);
});


console.log(files.map(file => `${sourceDir}/${file}`).join(' '));

console.log(subdirectoryFiles.map(file => `${sourceDir}/${file}`).join(' ').split(",").join(" ").replace(new RegExp('^src/'), ''));

exec(`mkdir -p ${buildDir}`);

// call g++
exec(`g++ -o ${buildDir}/main ${files.map(file => `${sourceDir}/${file}`).join(' ')} ${subdirectoryFiles.map(file => `${sourceDir}/${file}`).join(' ').split(",").join(" ").replace(new RegExp('^src/'), '')} `, (err, stdout, stderr) => {
    if (err) {
        console.error(err);
        return;
    }
    console.log(stdout);
});