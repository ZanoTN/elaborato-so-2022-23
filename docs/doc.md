## Message queue

| mtype            | Descrizione                            | Utilizzatore |
| :---             | :---                                   |         ---: |
| 1                | Invio richiesta ingresso partita       |       Client |
| 200000 + pid_t   | Risposta richiesta con informazioni    |       Server |
| 3                | Invio inizio partita                   |       Server |
| 100              | Trasmissione stato                     |       Client |


## Status code

| codice | Descrizione                                                    |
| :---   |                                                           ---: |
| 200    | L'utente che invia questo segnale ha vinto la partita          |
| 210    | L'utente che invia questo segnale ha pareggiato la partita     |