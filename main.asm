Start:
  loadi 1, $r16
  jump WaitForData
WaitForData:
  cmp $r16, $sr
  jumpne WaitForData
  jump ProcessData
ProcessData:
  shrli 6, $lrx
  shrli 6, $lry
  loadi 0, $r17
  shlli 8, $lry
  add   $lry, $r17
  add   $lrx, $r17  // Get the row
  jump  StoreData
StoreData:
  loadi 0, $r18
  add   $r17, $r18
  and   3, $r18   // Get the row  that we need to index into the word
  loadwordintomem $r18
  jump WaitForData
