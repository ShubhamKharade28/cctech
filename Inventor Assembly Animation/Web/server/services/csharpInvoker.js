const axios = require('axios');
const fs = require('fs');
const FormData = require('form-data');

// TODO: Should be run get data route
const sendToCSharp = async (dirPath) => {
    // try {
    //     const form = new FormData();
    //     const files = fs.readdirSync(dirPath);

    //     for (const file of files) {
    //         const filePath = `${dirPath}/${file}`;
    //         form.append('files', fs.createReadStream(filePath), file);
    //     }

    //     const response = await axios.post('http://localhost:6000/process', form, {
    //         headers: form.getHeaders()
    //     });

    //     return response.data;
    // } catch (error) {
    //     console.error('C# processor error:', error.message);
    //     return { error: 'C# processor failed' };
    // }

    // Todo: Perform above using exec(InventorExporterAlgo.exe, input_file, output_file);
    console.log("TODO: To perform execution of InventorExporterAlgo.exe using the input and output file");
};

module.exports = {
    sendToCSharp,
}