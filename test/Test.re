open Bot;
open Js.Promise;

bot({token: "<Your token here>"})
|> then_(bot => {
     Js.log(bot);
     resolve();
   })
|> catch(error => {
     Js.log(error);
     resolve();
   });

let rec hang = () => Js.Global.setTimeout(hang, 50000) |> ignore;