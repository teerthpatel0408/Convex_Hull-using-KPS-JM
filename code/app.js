// Import required modules
const express = require('express');
const fs = require('fs');
// Create an instance of Express
const app = express();
const path = require('path');
const bodyParser = require('body-parser');

app.use(express.static('public'))

app.use(bodyParser.urlencoded({ extended: false }))

// parse application/json
app.use(bodyParser.json())

app.get('/empty-points', (req, res) => {
    const filePath = path.join(__dirname, 'points.csv');

    // Truncate the file to empty its contents
    fs.truncate(filePath, 0, (err) => {
        if (err) {
            console.error('Error truncating file:', err);
            res.status(500).send('Error emptying file.');
            return;
        }
        console.log('File emptied successfully.');
        res.status(200).send('File emptied successfully.');
    });
});


const multer = require('multer');
const upload = multer({ dest: 'uploads/' });

app.post('/upload-csv', upload.single('file'), (req, res) => {
    if (!req.file) {
        res.status(400).send('No file uploaded.');
        return;
    }

    const csvPath = req.file.path;
    const fs = require('fs');

    fs.readFile(csvPath, 'utf8', (err, data) => {
        if (err) {
            console.error('Error reading uploaded CSV file:', err);
            res.status(500).send('Error reading uploaded CSV file.');
            return;
        }

        const pointsCsvPath = path.join(__dirname, 'points.csv');
        fs.appendFile(pointsCsvPath, data, 'utf8', (err) => {
            if (err) {
                console.error('Error appending CSV data to points.csv:', err);
                res.status(500).send('Error appending CSV data to points.csv.');
                return;
            }
            console.log('CSV data appended to points.csv.');
            res.status(200).send();
        });
    });
    // res.status(200).send;
});


// Define a route
app.get("/",function(req,res){
    res.sendFile(__dirname+"/index.html");
});

app.get("/generate-points", function(req, res) {
    // Execute the Python script
    console.log("/generate-points app.js");
    let val=Number(req.query.points);
    const spawn = require('child_process').spawn;
    const ls = spawn('python', ['randomPointsGenerator.py',val]);

    ls.stdout.on('data', (data) => {
        console.log(`stdout: ${data}`);
    });

    ls.stderr.on('data', (data) => {
        console.log(`stderr: ${data}`);
    });

    ls.on('close', (code) => {
        console.log(`child process exited with code ${code}`);
        res.json({ message: "Points generated successfully!" });
    });
});

// app.post('/your-backend-endpoint', (req, res) => {
//     const receivedData = req.body.data;
//     console.log(receivedData); // Handle the received data
//     res.send({ message: 'Data received successfully' });
//  });

 app.post('/append-to-points', (req, res) => {
    const csvPath = path.join(__dirname, 'points.csv');
    const csvData = req.body.data;
  
    fs.appendFile(csvPath, csvData, 'utf8', (err) => {
      if (err) {
        console.error('Error appending coordinates to points.csv:', err);
        res.status(500).send('Error appending coordinates to points.csv');
        return;
      }
      console.log('Coordinates appended to points.csv');
      res.status(200).send();
    });
  });
 

app.get('/points.csv', (req, res) => {
    // Define the path to points.csv
    console.log("/points.js app.js");
    const csvPath = path.join(__dirname, 'points.csv');

    fs.open(csvPath, 'r', (err, fd) => {
        if (err) {
            console.error('Error opening points.csv:', err);
            res.status(500).send('Error opening points.csv');
            return;
        }
    
        // Read the file
        fs.readFile(csvPath, 'utf8', (err, data) => {
            // Handle read operation
            if (err) {
                console.error('Error reading points.csv:', err);
                res.status(500).send('Error reading points.csv');
                return;
            }
            
            // Close the file after reading
            fs.close(fd, (err) => {
                if (err) {
                    console.error('Error closing points.csv:', err);
                    return;
                }
                console.log('File was closed successfully.');
            });

            res.set('Content-Type', 'text/csv');
            res.send(data);
        });
    });
});

app.get('/results/results_1.csv', (req, res) => {
    // Define the path to points.csv
    const csvPath = path.join(__dirname, 'results/results_1.csv');

    fs.open(csvPath, 'r', (err, fd) => {
        if (err) {
            console.error('Error opening points.csv:', err);
            res.status(500).send('Error opening points.csv');
            return;
        }
    
        // Read the file
        fs.readFile(csvPath, 'utf8', (err, data) => {
            // Handle read operation
            if (err) {
                console.error('Error reading points.csv:', err);
                res.status(500).send('Error reading points.csv');
                return;
            }
            
            // Close the file after reading
            fs.close(fd, (err) => {
                if (err) {
                    console.error('Error closing points.csv:', err);
                    return;
                }
                console.log('File was closed successfully.');
            });
            
            res.set('Content-Type', 'text/csv');
            res.send(data);
        });
    });
});

app.get("/run-cpp-program", function(req, res) {
    // Execute the Python script
    console.log("/run-cpp-program app.js");
    const spawn = require('child_process').spawn;
    console.log(req.query);
    if(req.query.algorithm=="jarvis"){
        const compileProcess = spawn('g++', ['JM.cpp', '-o', 'JM']);

        compileProcess.stdout.on('data', (data) => {
            console.log(`Compile stdout: ${data}`);
        });

        compileProcess.stderr.on('data', (data) => {
            console.error(`Compile stderr: ${data}`);
        });

        compileProcess.on('close', (code) => {
            console.log(`Compile process exited with code ${code}`);
            
            // Execute the compiled program if compilation was successful
            if (code === 0) {
                const executeProcess = spawn('./JM', []);

                executeProcess.stdout.on('data', (data) => {
                    console.log(`Execution stdout: ${data}`);
                });

                executeProcess.stderr.on('data', (data) => {
                    console.error(`Execution stderr: ${data}`);
                });

                executeProcess.on('close', (code) => {
                    console.log(`Execution process exited with code ${code}`);
                });
            }
        });
    }

    else{
        console.log("Vasu");
        const compileProcess = spawn('g++', ['KPS.cpp', '-o', 'KPS']);

        compileProcess.stdout.on('data', (data) => {
            console.log(`Compile stdout: ${data}`);
        });

        compileProcess.stderr.on('data', (data) => {
            console.error(`Compile stderr: ${data}`);
        });

        compileProcess.on('close', (code) => {
            console.log(`Compile process exited with code ${code}`);
            
            // Execute the compiled program if compilation was successful
            if (code === 0) {
                const executeProcess = spawn('./KPS', []);

                executeProcess.stdout.on('data', (data) => {
                    console.log(`Execution stdout: ${data}`);
                });

                executeProcess.stderr.on('data', (data) => {
                    console.error(`Execution stderr: ${data}`);
                });

                executeProcess.on('close', (code) => {
                    console.log(`Execution process exited with code ${code}`);
                });
            }
        });
    }
    res.status(200).send();
});

// Set the port for the server to listen on
const port = 3000;

// Start the server
app.listen(port, () => {
  console.log(`Server is running on port ${port}`);
});
