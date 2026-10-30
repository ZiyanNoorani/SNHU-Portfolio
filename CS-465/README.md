# CS-465 Full Stack Development

Travlr Getaways, a MEAN stack web application (MongoDB, Express, Angular, Node.js) built across the course modules.

## Module One: Express static site

The `travlr` folder is a Node.js and Express app generated with `express --view=hbs --git`. The Travlr Getaways HTML mockup pages live in `travlr/public`, with images in `public/images` and the stylesheet in `public/css`. Express serves them as static files.

## Run it locally

```
cd CS-465/travlr
npm install
npm start
```

Then open http://localhost:3000.

`node_modules` is not stored in the repo. `npm install` rebuilds it from `package.json`.
