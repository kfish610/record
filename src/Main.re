open Bot;
Js.Promise.(
  bot({token: ""})
  |> then_(bot => {
       Js.log(bot);
       resolve(bot);
     })
);