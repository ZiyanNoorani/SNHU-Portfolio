const mongoose = require('mongoose');
const host = process.env.DB_HOST || '127.0.0.1';
const dbURI = `mongodb://${host}/travlr`;
const readLine = require('readline');

// Build the connection string and set the connection timeout.
// timeout is in milliseconds.
const connect = () => {
    setTimeout(() => {
        mongoose.connect(dbURI, {
            serverSelectionTimeoutMS: 5000
        }).catch(err => {
            // Catch a failed first connection so it does not crash the app
            // with an unhandled promise rejection
            console.log('Mongoose initial connection failed: ', err.message);
        });
    }, 1000);
};

// Monitor connection events
mongoose.connection.on('connected', () => {
    console.log(`Mongoose connected to ${dbURI}`);
});

mongoose.connection.on('error', err => {
    console.log('Mongoose connection error: ', err);
});

mongoose.connection.on('disconnected', () => {
    console.log('Mongoose disconnected');
});

// Windows specific listener
if (process.platform === 'win32') {
    const r1 = readLine.createInterface({
        input: process.stdin,
        output: process.stdout
    });
    r1.on('SIGINT', () => {
        process.emit('SIGINT');
    });
}

// Configure for Graceful Shutdown
// Mongoose 7+ removed the callback form of connection.close(),
// so this uses the promise form and waits for it to finish.
const gracefulShutdown = async (msg) => {
    try {
        await mongoose.connection.close();
        console.log(`Mongoose disconnected through ${msg}`);
    } catch (err) {
        console.log(`Error closing Mongoose connection through ${msg}: `, err);
    }
};

// Event Listeners to process graceful shutdowns

// Shutdown invoked by nodemon signal
process.once('SIGUSR2', async () => {
    await gracefulShutdown('nodemon restart');
    process.kill(process.pid, 'SIGUSR2');
});

// Shutdown invoked by app termination
process.on('SIGINT', async () => {
    await gracefulShutdown('app termination');
    process.exit(0);
});

// Shutdown invoked by container termination
process.on('SIGTERM', async () => {
    await gracefulShutdown('app shutdown');
    process.exit(0);
});

// Make initial connection to DB
connect();

// Import Mongoose schema
require('./travlr');
module.exports = mongoose;
