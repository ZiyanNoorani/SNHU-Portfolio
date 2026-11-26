const mongoose = require('mongoose');
const Trip = require('../models/travlr'); // Register model
const Model = mongoose.model('trips');

// GET: /trips - lists all the trips
// Regardless of outcome, response must include HTML status code
// and JSON message to the requesting client
const tripsList = async (req, res) => {
    try {
        const q = await Model
            .find({}) // No filter, return all records
            .exec();

        // Uncomment the following line to show results of query
        // on the console
        // console.log(q);

        if (!q) { // Database returned no data
            return res
                .status(404)
                .json({ message: 'No trips found' });
        }

        // An empty collection is still a valid list, so it returns 200 []
        return res // Return resulting trip list
            .status(200)
            .json(q);
    } catch (err) { // Database or connection error
        return res
            .status(500)
            .json({ message: 'Error retrieving trips', error: err.message });
    }
};

// GET: /trips/:tripCode - lists a single trip
// Regardless of outcome, response must include HTML status code
// and JSON message to the requesting client
const tripsFindByCode = async (req, res) => {
    try {
        const q = await Model
            .find({ 'code': req.params.tripCode }) // Return single record
            .exec();

        // Uncomment the following line to show results of query
        // on the console
        // console.log(q);

        if (!q || q.length === 0) { // No trip matches that code
            return res
                .status(404)
                .json({ message: `Trip not found: ${req.params.tripCode}` });
        }

        return res // Return resulting trip
            .status(200)
            .json(q);
    } catch (err) { // Database or connection error
        return res
            .status(500)
            .json({ message: 'Error retrieving trip', error: err.message });
    }
};

module.exports = {
    tripsList,
    tripsFindByCode
};
