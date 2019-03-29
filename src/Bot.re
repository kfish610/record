type t = {token: string};
type botSettings = {token: string};
let bot: botSettings => Js.Promise.t(t) =
  settings =>
    Js.Promise.make((~resolve, ~reject) =>
      resolve(. {token: settings.token}: t)
    );