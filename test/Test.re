open Bot;
open Js.Promise;

let token = Js.Json.parseExn(Node.Fs.readFileSync("bot-settings.json", `utf8)) -> Js.Json.decodeObject -> Belt.Option.getExn -> Js.Dict.get("token") -> Belt.Option.getExn -> Js.Json.decodeString -> Belt.Option.getExn

bot({token: token})
|> then_(bot => {
     Js.log(bot);
     resolve();
   })
|> catch(error => {
     Js.log(error);
     resolve();
   });

let rec hang = () => Js.Global.setTimeout(hang, 50000) |> ignore;