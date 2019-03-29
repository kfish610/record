type botSettings = {token: string};
type t = {
  settings: botSettings,
  ws: WebSocket.t,
};
let bot =
  settings =>
    Js.Promise.make((~resolve, ~reject) => {
      let ws = WebSocket.make("wss://gateway.discord.gg/?v=6&encoding=json");
      WebSocket.(ws->on(`open_(() => Js.log("Opened")))->ignore);
      resolve(. {settings, ws});
    });