var arr = [];
var hullPoints = [];
var svgContainer = document.getElementById('svg-container');

window.addEventListener('beforeunload', function(event) {
  // Perform a fetch request to the "/empty-points" route

  fetch('/empty-points', {
      method: 'GET'
  })
  .then(response => {
      if (!response.ok) {
          throw new Error('Failed to empty points file.');
      }
      console.log('Points file emptied successfully.');
  })
  .catch(error => {
      console.error('Error emptying points file:', error);
  });
});

document.getElementById('skipAnimation').addEventListener('click',skipAnimation);

function skipAnimation(event){
  event.preventDefault();
  fetch("/results/results_1.csv")
    .then((response) => response.text())
    .then((data) => {
      // Parse the CSV data
      hullPoints = parseCSV(data);
      const algo = document.getElementById("algorithm").value;
      drawHullPointswithSkip(algo);
    })
    .catch((error) => {
      console.error("Error fetching file:", error);
    });

  console.log("HullPoints: " + hullPoints.length);
}

// document.getElementById('emptyPointsBtn').addEventListener('click', emptyPoints);

// function emptyPoints(event) {
//     event.preventDefault();
//     fetch('/empty-points', {
//         method: 'GET'
//     })
//     .then(response => {
//         if (!response.ok) {
//             throw new Error('Failed to empty points file.');
//         }
//         console.log('Points file emptied successfully.');
//     })
//     .catch(error => {
//         console.error('Error emptying points file:', error);
//         // Handle the error, e.g., display a message to the user
//         alert('Error emptying points file. Please try again.');
//     });
// }

document.getElementById('uploadBtn').addEventListener('click', uploadCSV);

function uploadCSV(event) {
    event.preventDefault();
    const fileInput = document.getElementById('csvFileInput');
    const file = fileInput.files[0];

    if (!file) {
        console.error('No file selected.');
        return;
    }

    const formData = new FormData();
    formData.append('file', file);

    fetch('/upload-csv', {
        method: 'POST',
        body: formData
    })
    .then(response => {
        if (!response.ok) {
            throw new Error('Failed to upload CSV file.');
        }
        console.log('CSV file uploaded successfully.');
    })
    .catch(error => {
        console.error('Error uploading CSV file:', error);
    });
}


// Function to parse CSV data
function parseCSV(csv) {
  console.log("Chodu");
  // Split the CSV by lines
  const lines = csv.split("\n");
  // Initialize an empty array to store points
  const points = [];
  // Loop through each line
  lines.forEach((line) => {
    // Split each line by comma
    const parts = line.split(",");
    // Extract x and y coordinates
    const x = parseFloat(parts[0]);
    const y = parseFloat(parts[1]);
    // Check if coordinates are valid numbers
    if (!isNaN(x) && !isNaN(y)) {
      // Push the point object into the array
      points.push({ x, y });
    } else {
      console.log(`Skipping invalid coordinates: x=${x}, y=${y}`);
    }
  });
  return points;
}

function drawPoints() {
  console.log("Fuck" + arr.length);
  var visualizationContainer = document.getElementById(
    "visualization-container"
  );
  for (let i = 0; i < arr.length; i++) {
    var dot = createDot(arr[i].x, arr[i].y);
    arr.pop();
    console.log(arr[i].x + " " + arr[i].y);
    visualizationContainer.appendChild(dot);
  }
}

function markpoint(pts,color)
{
  
  var pt=document.getElementById('x'+Math.abs(pts.x)+'y'+Math.abs(pts.y));
  
  pt.style.backgroundColor=color;
}
function unmarkpoint(pts)
{
  var pt=document.getElementById('x'+Math.abs(pts.x)+'y'+Math.abs(pts.y));
  pt.style.backgroundColor="black";
}

function connectDots(pts1,pts2,color) {
  x1=Math.abs(pts1.x);
  x2=Math.abs(pts2.x);
  y1=Math.abs(pts1.y);
  y2=Math.abs(pts2.y);
  var line = document.createElementNS("http://www.w3.org/2000/svg", "line");
    line.id="x1"+x1+"y1"+y1+"x2"+x2+"y2"+y2+"c"+color;
    line.setAttribute("x1", x1);
    line.setAttribute("y1", y1);
    line.setAttribute("x2", x2);
    line.setAttribute("y2", y2);
    line.setAttribute("stroke",color); // Adjust color as needed
    line.setAttribute("class", "line");
    svgContainer.appendChild(line);
  return line
  }
function disconnect(pts1,pts2,color)
{
   let lineid="x1"+Math.abs(pts1.x)+"y1"+Math.abs(pts1.y)+"x2"+Math.abs(pts2.x)+"y2"+Math.abs(pts2.y)+"c"+color;
   var lin=document.getElementById(lineid);
   svgContainer.removeChild(lin);
}

function sleep(ms) {
  return new Promise((resolve) => setTimeout(resolve, ms));
}

async function drawLinesWithDelayKPS(){
  console.log("Stuti");
  for(let i=0;i<hullPoints.length;i++){
    markpoint(hullPoints[i],'red');
  }
  await sleep(1000);
  for(let j=0;j<hullPoints.length;j+=2){
    connectDots(hullPoints[j],hullPoints[j+1],'blue');
    await sleep(1000);
  }
}

function drawHullPointswithSkip(algo){
  if(algo=="jarvis"){
    for(let i=0;i<hullPoints.length;i++){
      markpoint(hullPoints[i],'red');
    }
    for(let j=0;j<hullPoints.length-1;j++){
      connectDots(hullPoints[j],hullPoints[j+1],'blue');
    }
    connectDots(hullPoints[0],hullPoints[hullPoints.length-1],'blue');
  }
  else{
    for(let i=0;i<hullPoints.length;i++){
      markpoint(hullPoints[i],'red');
    }
    for(let j=0;j<hullPoints.length;j+=2){
      connectDots(hullPoints[j],hullPoints[j+1],'blue');
    }
  }
  
}

async function drawLinesWithDelayJarvis(){
  for(let i=0;i<hullPoints.length;i++){
    for(let j=0;j<arr.length;j++){
      markpoint(hullPoints[i],'red');
      markpoint(arr[j],'green');
      var line=connectDots(hullPoints[i],arr[j],'orange');
      await sleep(100);
      line.parentNode.removeChild(line);
      unmarkpoint(arr[j]);
      // if(hullPoints.includes(arr[j])){
      //   markpoint(arr[j],'red');
      // }
    }
    if(i==hullPoints.length-1){
      connectDots(hullPoints[0],hullPoints[hullPoints.length-1],'blue');
    }
    else{
      connectDots(hullPoints[i],hullPoints[i+1],'blue');
    }
    unmarkpoint(hullPoints[i]);
  }
  
}

function drawHullPoints(){
  const algo = document.getElementById("algorithm").value;
  if (algo == "jarvis") {
        drawLinesWithDelayJarvis();
  } 
  else {
      drawLinesWithDelayKPS();
  }
}

// Remove event listeners when elements are removed from the DOM
document
  .getElementById("visualize")
  .removeEventListener("click", visualizeHandler);
document
  .getElementById("generate")
  .removeEventListener("click", generateHandler);
document
  .getElementById("run")
  .removeEventListener("click", runAlgorithmHandler);
document
  .getElementById("show")
  .removeEventListener("click", showResultsHandler);
document
  .getElementById("visualization-container")
  .removeEventListener("click", addPointsHandler);

// Add event listeners only after the DOM content is loaded
document.addEventListener("DOMContentLoaded", () => {
  document
    .getElementById("visualize")
    .addEventListener("click", visualizeHandler);
  document
    .getElementById("generate")
    .addEventListener("click", generateHandler);
  document.getElementById("run").addEventListener("click", runAlgorithmHandler);
  document.getElementById("show").addEventListener("click", showResultsHandler);
  document
    .getElementById("visualization-container")
    .addEventListener("click", addPointsHandler);
});

function createDot(x, y) {
  var dot = document.createElement("div");
  dot.className = "dot";
  dot.id = "x" + x + "y" + y;
  dot.style.left = x - 5 + "px";
  dot.style.top = y - 5 + "px";
  arr.push({ x, y });
  return dot;
}

function addPointsHandler(event) {
  var dot = createDot(event.offsetX, event.offsetY);
  this.appendChild(dot);
  const x=event.offsetX;
  const y=event.offsetY;

  const sendData = async () => {
    const csvData = `${x},${y}\n`; // Your string data
    const response = await fetch('/append-to-points', {
        method: 'POST',
        headers: {
            'Content-Type': 'application/json'
        },
        body: JSON.stringify({ data: csvData })  // Ensure data is properly stringified
    });
    const responseData = await response.json();
    console.log(responseData); // Handle response from the backend
 };
 
 sendData();
 
}

// Define event handler functions
function visualizeHandler(event) {
  // Your visualization logic here
  event.preventDefault();
  console.log("Hello");
  fetch("/points.csv")
    .then((response) => response.text())
    .then((data) => {
      // Parse the CSV data
      arr = parseCSV(data);
      drawPoints();
    })
    .catch((error) => {
      console.error("Error fetching file:", error);
    });
}

function generateHandler(event) {
  // Your generation logic here

  var dots = document.querySelectorAll(".dot");
  dots.forEach(function (dot) {
    dot.parentNode.removeChild(dot);
  });
  var lines = document.querySelectorAll(".line");
  lines.forEach(function (l) {
    l.parentNode.removeChild(l);
  });
  arr = [];
  hullPoints = [];
  event.preventDefault();

  // Get the number of points from the input field
  const numPoints = document.getElementById("points").value;

  // Fetch the data using AJAX, passing the number of points as a query parameter
  fetch(`/generate-points?points=${numPoints}`)
    .then((response) => {
      // Check if the response is successful
      if (response.ok) {
        // If successful, stop further processing
        return;
      } else {
        // If not successful, handle the error
        throw new Error("Failed to generate points");
      }
    })
    .catch((error) => {
      // Handle errors
      console.error("Error generating points:", error);
    });
}

function runAlgorithmHandler(event) {
  // Your algorithm execution logic here
  event.preventDefault();
  console.log("Love");
  // Get the selected algorithm name from the dropdown
  const algorithm = document.getElementById("algorithm").value;

  // Fetch the data using AJAX, passing the algorithm name as a query parameter
  fetch(`/run-cpp-program?algorithm=${algorithm}`)
    .then((response) => {
      // Check if the response is successful
      if (response.ok) {
        // If successful, stop further processing
        return;
      } else {
        // If not successful, handle the error
        throw new Error("Failed to run algorithm");
      }
    })
    .catch((error) => {
      // Handle errors
      console.error("Error running algorithm:", error);
    });
}

function showResultsHandler(event) {
  // Your results display logic here
  event.preventDefault();
  fetch("/results/results_1.csv")
    .then((response) => response.text())
    .then((data) => {
      // Parse the CSV data
      hullPoints = parseCSV(data);
      drawHullPoints();
    })
    .catch((error) => {
      console.error("Error fetching file:", error);
    });

  console.log("HullPoints: " + hullPoints.length);
}
