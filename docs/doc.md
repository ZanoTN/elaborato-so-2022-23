## Message queue

| mtype            | Descrizione                            | Utilizzatore |
| :---             | :---                                   |         ---: |
| 1                | Invio richiesta ingresso partita       |       Client |
| 200000 + pid_t   | Risposta richiesta con informazioni    |       Server |
| 3                | Invio inizio partita                   |       Server |
| 100              | Trasmissione stato                     |       Client |
