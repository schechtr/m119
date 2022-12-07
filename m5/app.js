const express = require('express'); //Import the express dependency
const app = express();              //Instantiate an express app, the main work horse of this server
const port = 8080;                  //Save the port number where your server will be listening

// Point express to our public directory
app.use(express.static(__dirname + "/public/"));

// Idiomatic expression in express to route and respond to a client request
app.get('/', (req, res) => {   
    res.sendFile('index.html', {root: __dirname});      
                                                        
});

// Server starts listening for any attempts from a client to connect at port: {port}
app.listen(port, () => {           
    console.log(`Now listening on port ${port}`); 
});