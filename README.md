# Elaborato sistemi operativi 2022-2023
_Riccardo Zanotelli, Leonora Lika_
## Organizzazione dei file
I file devono essere posizionati nelle corrette cartelle:
- **src**: Tutti i file ".c" riguardanti sia per il client che per il server.
- **inc**: Tutti i ".h".
- **docs**: Qui saranno posizionati tutti i file ".md" riguardati la relazione o eventuale documentazione delle librerie del progetto.
- **.vscode**: Questa è una cartella di configurazione quindi sarà presente nella repo e contiene la configurazione per lavorare con VSCode.

Per una corretta gestione dei .h e .c si dovrà prevedere a importare le librerie nei .c dove possibile e commentare sempre le funzioni con l'apposito strumento (*/// @brief...*, maggiori info [qua](https://devblogs.microsoft.com/cppblog/visual-studio-code-c-extension-july-2020-update-doxygen-comments-and-logpoints/)).


Nella repository sono presenti anche i file Makefile.F4Server, Makefile.Client e LICENSE, anche quelli non devono essere cancellati e soprattuto il file LICENSE non deve essere toccato.

## Compilazione
La compilazione dei due eseguibili viene fatta attraverso il sistema makefile:

```
All:		make
Server:		make -f Makefile.F4Server
Client:		make -f Makefile.F4Client
```

Nel caso di aggiunta di sorgenti e/o lib è necessario aggiornare le configurazioni.