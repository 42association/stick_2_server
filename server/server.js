const express = require('express');
const bodyParser = require('body-parser');

const app = express();
app.use(bodyParser.urlencoded({ extended: true }));

app.post('/api/data', (req, res) => {
	const message = req.body.message;
	console.log('Received message:', message);

	// 処理

	res.send('Message received');
});

const port = 8080;
app.listen(port, () => {
	console.log(`Server started on port ${port}`);
});