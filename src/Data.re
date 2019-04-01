module Presence = Data_presence;

module User = Data_user;

module Guild = Data_guild;

exception NotImplemented;

type updateStatus = {
  since: option(int),
  game: option(Presence.activity),
  status: string,
  afk: bool,
};

type ready = {
  v: int,
  user: User.user,
  private_channels: array(unit),
  guilds: array(Guild.unavailableGuild),
  session_id: string,
  trace: array(string),
  shard: option(array(int)),
};

type heartbeat = Js.null(int);

type identify = {
  token: string,
  properties: props,
  compress: option(bool),
  large_threshold: option(int),
  shard: option(array(int)),
  presence: option(updateStatus),
}
and props = {
  os: string,
  browser: string,
  device: string,
};

type hello = {
  heartbeat_interval: int,
  trace: array(string),
};

type event =
  | Ready(ready);

type payload =
  | Event(event)
  | Heartbeat(heartbeat)
  | Identify(identify)
  | Hello(hello)
  | Ack;

type data = {
  op: int,
  d: payload,
  s: option(int),
  t: option(string),
};

let op_of_payload = payload =>
  switch (payload) {
  | Event(_) => 0
  | Heartbeat(_) => 1
  | Identify(_) => 2
  | Hello(_) => 10
  | Ack => 11
  };

let t_of_payload = payload =>
  switch (payload) {
  | Event(event) =>
    Some(
      switch (event) {
      | Ready(_) => "READY"
      },
    )
  | _ => None
  };

module Decode = {
  module User = {
    open User;

    let user = json =>
      Json.Decode.{
        id: json |> field("id", string),
        username: json |> field("username", string),
        discriminator: json |> field("discriminator", string),
        avatar: json |> field("avatar", nullable(string)),
        bot: json |> field("bot", optional(bool)),
        mfa_enabled: json |> optional(field("mfa_enabled", bool)),
        locale: json |> optional(field("locale", string)),
        verified: json |> optional(field("verified", bool)),
        email: json |> optional(field("email", string)),
        flags: json |> optional(field("flags", int)),
        premium_type: json |> optional(field("premium_type", int)),
      };
  };

  module Guild = {
    open Guild;

    let unavailableGuild = json =>
      Json.Decode.{
        id: json |> field("id", string),
        unavailable: json |> field("unavailable", bool),
      };
  };

  let ready = json =>
    Event(
      Ready(
        Json.Decode.{
          v: json |> field("v", int),
          user: json |> field("user", User.user),
          private_channels: json |> field("private_channels", array(_ => ())),
          guilds: json |> field("guilds", array(Guild.unavailableGuild)),
          session_id: json |> field("session_id", string),
          trace: json |> field("_trace", array(string)),
          shard: json |> optional(field("shard", array(int))),
        },
      ),
    );

  let hello = json =>
    Hello(
      Json.Decode.{
        heartbeat_interval: json |> field("heartbeat_interval", int),
        trace: json |> field("_trace", array(string)),
      },
    );

  let data = json =>
    Json.Decode.{
      op: json |> field("op", int),
      d:
        json
        |> field(
             "d",
             switch (json |> field("op", int)) {
             | 0 =>
               switch (json |> field("t", string)) {
               | "READY" => ready
               | _ => raise(NotImplemented)
               }
             | 10 => hello
             | 11 => (_ => Ack)
             | _ => raise(NotImplemented)
             },
           ),

      s: json |> optional(field("s", int)),
      t: json |> optional(field("t", string)),
    };
};

module Encode = {
  let required = (encoder, r) => Some(encoder(r));

  let optional = (encoder, r) =>
    switch (r) {
    | Some(x) => Some(encoder(x))
    | None => None
    };
  
  let null = (encoder, r) =>
    switch (r) {
    | x when x == Js.null => Json.Encode.null
    | x => encoder(Js.Null.getExn(x))
    }

  let object__ = fields =>
    List.fold_right(
      (b, a) =>
        switch (b) {
        | (str, Some(json)) => [(str, json), ...a]
        | (_, None) => a
        },
      fields,
      [],
    )
    |> Json.Encode.object_;

  module Presence = {
    open Presence;

    let activityTimestamps = r =>
      Json.Encode.(
        object__([
          ("start", r.start |> optional(int)),
          ("end", r.end_ |> optional(int)),
        ])
      );

    let activityParty = r =>
      Json.Encode.(
        object__([
          ("id", r.id |> optional(string)),
          ("size", r.size |> optional(array(int))),
        ])
      );

    let activityAssets = r =>
      Json.Encode.(
        object__([
          ("large_image", r.large_image |> optional(string)),
          ("large_text", r.large_text |> optional(string)),
          ("small_image", r.small_image |> optional(string)),
          ("small_text", r.small_text |> optional(string)),
        ])
      );

    let activitySecrets = r =>
      Json.Encode.(
        object__([
          ("join", r.join |> optional(string)),
          ("spectate", r.spectate |> optional(string)),
          ("match", r.match |> optional(string)),
        ])
      );

    let activity = r =>
      Json.Encode.(
        object__([
          ("name", r.name |> required(string)),
          ("type", r.type_ |> required(int)),
          ("url", r.url |> optional(string)),
          ("timestamps", r.timestamps |> optional(activityTimestamps)),
          ("application_id", r.application_id |> optional(string)),
          ("details", r.details |> optional(string)),
          ("state", r.state |> optional(string)),
          ("party", r.party |> optional(activityParty)),
          ("assets", r.assets |> optional(activityAssets)),
          ("secrets", r.secrets |> optional(activitySecrets)),
          ("instance", r.instance |> optional(bool)),
          ("flags", r.flags |> optional(int)),
        ])
      );
  };

  let updateStatus = r =>
    Json.Encode.(
      object__([
        ("since", r.since |> optional(int)),
        ("game", r.game |> optional(Presence.activity)),
        ("status", r.status |> required(string)),
        ("afk", r.afk |> required(bool)),
      ])
    );

  let heartbeat = null(Json.Encode.int);

  let props = r =>
    Json.Encode.(
      object_([
        ("$os", r.os |> string),
        ("$browser", r.browser |> string),
        ("$device", r.device |> string),
      ])
    );

  let identify = r =>
    Json.Encode.(
      object__([
        ("token", r.token |> required(string)),
        ("properties", r.properties |> required(props)),
        ("compress", r.compress |> optional(bool)),
        ("large_threshold", r.large_threshold |> optional(int)),
        ("shard", r.shard |> optional(array(int))),
        ("presence", r.presence |> optional(updateStatus)),
      ])
    );

  let hello = r =>
    Json.Encode.(
      object_([
        ("heartbeat_interval", r.heartbeat_interval |> int),
        ("_trace", r.trace |> array(string)),
      ])
    );

  let data = r =>
    Json.Encode.(
      object__([
        ("op", r.op |> required(int)),
        (
          "d",
          switch (r.d) {
          | Heartbeat(payload) => payload |> required(heartbeat)
          | Identify(payload) => payload |> required(identify)
          | _ => None
          },
        ),
        ("s", r.s |> optional(int)),
        ("t", r.t |> optional(string)),
      ])
    );

  let dataFromPayload = r =>
    Json.Encode.(
      object__([
        ("op", op_of_payload(r) |> required(int)),
        (
          "d",
          switch (r) {
          | Heartbeat(payload) => payload |> required(heartbeat)
          | Identify(payload) => payload |> required(identify)
          | _ => None
          },
        ),
        ("t", t_of_payload(r) |> optional(string)),
      ])
    );
};