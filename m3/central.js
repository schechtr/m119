// based on the example on https://www.npmjs.com/package/@abandonware/noble

const noble = require('@abandonware/noble');

const uuid_service = "1101"
const uuid_values = ['2101', '2102', '2103'];

let sensorValueX = NaN
let sensorValueY = NaN
let sensorValueZ = NaN

noble.on('stateChange', async (state) => {
    if (state === 'poweredOn') {
        console.log("start scanning")
        await noble.startScanningAsync([uuid_service], false);
    }
});

noble.on('discover', async (peripheral) => {
    await noble.stopScanningAsync();
    await peripheral.connectAsync();
    const {
        characteristics
    } = await peripheral.discoverSomeServicesAndCharacteristicsAsync([uuid_service], uuid_values);
    readData(characteristics)
});

//
// read data periodically
//
let readData = async (characteristics) => {
    const xvalue = (await characteristics[0].readAsync())
    const yvalue = (await characteristics[1].readAsync())
    const zvalue = (await characteristics[2].readAsync())

    sensorValueX = xvalue.readFloatLE(0);
    sensorValueY = yvalue.readFloatLE(0);
    sensorValueZ = zvalue.readFloatLE(0);

    console.log(sensorValueX + ','+ sensorValueY + ',' + sensorValueZ);

    // read data again in t milliseconds
    setTimeout(() => {
        readData(characteristics)
    }, 10);
}

//
// hosting a web-based front-end and respond requests with sensor data
// based on example code on https://expressjs.com/
//
const express = require('express')
const cors = require('cors')
const app = express()
const port = 3000

app.use(cors())

// Idiomatic expression in express to route and respond to a client request
app.get('/', (req, res) => {   
    res.sendFile('index.html', {root: __dirname});      
                                                        
});

app.post('/', (req, res) => {
    res.writeHead(200, {
        'Content-Type': 'application/json'
    });
    res.end(JSON.stringify({
        sensorValueX: sensorValueX,
        sensorValueY: sensorValueY,
        sensorValueZ: sensorValueZ
    }))
})

app.listen(port, () => {
    console.log(`Example app listening on port ${port}`)
})
  
