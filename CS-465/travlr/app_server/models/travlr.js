const mongoose = require('mongoose');

// Define the trip schema
// code and name are indexed for faster lookups.
// start is stored as a Date (ISO 8601 format in MongoDB).
const tripSchema = new mongoose.Schema({
    code: { type: String, required: true, index: true },
    name: { type: String, required: true, index: true },
    length: { type: String, required: true },
    start: { type: Date, required: true },
    resort: { type: String, required: true },
    perPerson: { type: String, required: true },
    image: { type: String, required: true },
    description: { type: String, required: true }
});

// Model name 'trips' maps to the 'trips' collection in the travlr database
const Trip = mongoose.model('trips', tripSchema);
module.exports = Trip;
