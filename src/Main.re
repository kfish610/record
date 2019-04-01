open Bot;
Js.Promise.(
  bot({token: ""})
  |> then_(bot => {
       Js.log(bot);
       resolve(bot);
     })
);

let rec hang = () => Js.Global.setTimeout(hang, 50000) |> ignore;