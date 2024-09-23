# SimpleTCP

A simple server that accepts the client's connection and writes its messages to log.txt

## Example

Server:

```
server 3000
```

Client:

```
client Name1 3000 5
```

Log.txt

```
[2024-09-16 12:00:00.12341234] Name1
[2024-09-16 12:00:05.43214321] Name1
[2024-09-16 12:00:10.12344321] Name1
```
