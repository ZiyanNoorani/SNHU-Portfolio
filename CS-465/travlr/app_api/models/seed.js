// Bring in the DB connection and the Trip schema
const Mongoose = require('./db');
const Trip = require('./travlr');

// Read seed data from json file
// Run this script from the travlr project root so the relative path resolves:
//   node .\app_server\models\seed
var fs = require('fs');
var trips = JSON.parse(fs.readFileSync('./data/trips.json', 'utf8'));

// delete any existing records, then insert seed data
const seedDB = async () => {
    await Trip.deleteMany({});
    await Trip.insertMany(trips);   // insertMany validates each record against tripSchema

    // Read the records back through Mongoose and print them as JSON
    // to confirm the data was stored in the right format
    const saved = await Trip.find({}).lean();
    console.log(`Seeded ${saved.length} trips into the travlr database:`);
    console.log(JSON.stringify(saved, null, 2));
};

// Close the MongoDB connection and exit
seedDB()
    .then(async () => {
        await Mongoose.connection.close();
        process.exit(0);
    })
    .catch(async (err) => {
        console.log('Seeding failed: ', err.message);
        await Mongoose.connection.close();
        process.exit(1);
    });
