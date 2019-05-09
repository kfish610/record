// Generated by BUCKLESCRIPT VERSION 5.0.0, PLEASE EDIT WITH CARE
'use strict';

var Fs = require("fs");
var Block = require("bs-platform/lib/js/block.js");
var Js_dict = require("bs-platform/lib/js/js_dict.js");
var Js_json = require("bs-platform/lib/js/js_json.js");
var Bot$Record = require("../src/Bot.bs.js");
var Belt_Option = require("bs-platform/lib/js/belt_Option.js");

var token = Belt_Option.getExn(Js_json.decodeString(Belt_Option.getExn(Js_dict.get(Belt_Option.getExn(Js_json.decodeObject(JSON.parse(Fs.readFileSync("bot-settings.json", "utf8")))), "token"))));

Bot$Record.bot(/* record */Block.record(["token"], [token])).then((function (bot) {
          console.log(bot);
          return Promise.resolve(/* () */0);
        })).catch((function (error) {
        console.log(error);
        return Promise.resolve(/* () */0);
      }));

function hang(param) {
  setTimeout(hang, 50000);
  return /* () */0;
}

exports.token = token;
exports.hang = hang;
/* token Not a pure module */