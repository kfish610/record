open Bot;
Js.Promise.(
  bot({token: "<your token here>"})
  |> then_(bot => {
       Js.log(bot);
       resolve(bot);
     })
);

let rec hang = () => Js.Global.setTimeout(hang, 50000) |> ignore;