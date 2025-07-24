let ws = require('ws')
var server = new ws.Server({port:8080});

server.on('connection', ws => {
    ws.on('message', message => {
        console.log(message.toString("utf8"));

        server.clients.forEach(client => {
            if (client.readyState == ws.OPEN)
                client.send(message.toString("utf8"));
        });
    });

    ws.on('close', () => {
        console.log('close');
    });
});