# RTA-DL3-Sim

Il tool RTA-DL3-Sim è un software che simula l'arrivo di dati DL3 che memorizza in un database sql.
Il software riceve 6 parametri di input:

1. fitsFileNamePath: Input fits file path.
2. idObs: Observation id.
3. idRepo: Repository id.
4. rate: How events per second insert in DB.
5. userId: Input database user id.
6. userPwd: Input database user password

Ricevuti i parametri di input il software estrae gli eventi contenuti all'interno del file fits e simula l'arrivo di eventi con un rate pari al valore rate dato in input.
Se ad esempio il valore di input rate è pari a 1000 sarà simulato l'arrivo di 1000 eventi in un secondo.
Questi eventi saranno memorizzati all'interno  di un database sql.

## Esempio di utilizzo:

  ./bin/RTA-DL3-Sim ../../../dl3_example/astri_000_41_001_00001_R_000001_001_0201_C3_RTA_v0.fits 1 2 1000 userId userPwd
