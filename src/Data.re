type optional('a) =
  | Field('a)
  | Missing;

type snowflake = string;

module Permissions = {
  type role = {
    id: snowflake,
    name: string,
    color: int,
    hoist: bool,
    position: int,
    permissions: int,
    managed: bool,
    mentionable: bool,
  };
};

module User = {
  type t = {
    id: snowflake,
    username: string,
    discriminator: string,
    avatar: option(string),
    bot: optional(bool),
    mfa_enabled: optional(bool),
    locale: optional(string),
    verified: optional(bool),
    email: optional(string),
    flags: optional(int),
    premium_type: optional(int),
  };
};

module Presence = {
  type timestamps = {
    start: optional(int),
    end_: optional(int),
  };

  type party = {
    id: optional(string),
    size: optional(array(int)),
  };

  type assets = {
    large_image: optional(string),
    large_text: optional(string),
    small_image: optional(string),
    small_text: optional(string),
  };

  type secrets = {
    join: optional(string),
    spectate: optional(string),
    match: optional(string),
  };

  type activity = {
    name: string,
    type_: int,
    url: optional(option(string)),
    timestamps: optional(timestamps),
    application_id: optional(snowflake),
    details: optional(option(string)),
    state: optional(option(string)),
    party: optional(party),
    assets: optional(assets),
    secrets: optional(secrets),
    instance: optional(bool),
    flags: optional(int),
  };

  type update = {
    user: User.t,
    roles: array(snowflake),
    game: option(activity),
    guild_id: snowflake,
    status: string,
    activities: array(activity),
    client_status: clientStatus,
  }
  and clientStatus = {
    desktop: optional(string),
    mobile: optional(string),
    web: optional(string),
  };
};

module Channel = {
  type overwrite = {
    id: snowflake,
    type_: string,
    allow: int,
    deny: int,
  };

  type t = {
    id: snowflake,
    type_: int,
    guild_id: optional(snowflake),
    position: optional(int),
    permission_overwrites: optional(array(overwrite)),
    name: optional(string),
    topic: optional(option(string)),
    nsfw: optional(bool),
    last_message_id: optional(option(snowflake)),
    bitrate: optional(int),
    user_limit: optional(int),
    rate_limit_per_user: optional(int),
    recipients: optional(array(User.t)),
    icon: optional(option(string)),
    owner_id: optional(snowflake),
    application_id: optional(snowflake),
    parent_id: optional(option(snowflake)),
    last_pin_timestamp: optional(Js.Date.t),
  };
};

module Emoji = {
  type t = {
    id: option(snowflake),
    name: string,
    roles: optional(array(string)),
    user: optional(User.t),
    require_colons: optional(bool),
    managed: optional(bool),
    animated: optional(bool),
  };
};

module rec Voice: {
  type state = {
    guild_id: snowflake,
    channel_id: option(snowflake),
    user_id: snowflake,
    member: optional(Guild.member),
  };
} = {
  type state = {
    guild_id: snowflake,
    channel_id: option(snowflake),
    user_id: snowflake,
    member: optional(Guild.member),
  };
}
and Guild: {
  type member = {
    user: User.t,
    nick: optional(string),
    roles: array(string),
    joined_at: Js.Date.t,
    deaf: bool,
    mute: bool,
  };

  type unavailable = {
    id: string,
    unavailable: bool,
  };

  type t = {
    id: snowflake,
    name: string,
    icon: option(string),
    splash: option(string),
    owner: optional(bool),
    owner_id: snowflake,
    permissions: optional(int),
    region: string,
    afk_channel_id: option(snowflake),
    afk_timeout: int,
    embed_enabled: optional(bool),
    embed_channel_id: optional(snowflake),
    verification_level: int,
    default_message_notifications: int,
    explicit_content_filter: int,
    roles: array(Permissions.role),
    emojis: array(Emoji.t),
    features: array(string),
    mfa_level: int,
    application_id: option(snowflake),
    widget_enabled: optional(bool),
    widget_channel_id: optional(snowflake),
    system_channel_id: option(snowflake),
    joined_at: optional(Js.Date.t),
    large: optional(bool),
    unavailable: optional(bool),
    member_count: optional(int),
    voice_states: optional(array(Voice.state)),
    members: optional(array(member)),
    channels: optional(array(Channel.t)),
    presences: optional(array(Presence.update)),
    max_presences: optional(option(int)),
    max_members: optional(int),
    vanity_url_code: option(string),
    description: option(string),
    banner: option(string),
  };

  type create = t;
} = {
  type member = {
    user: User.t,
    nick: optional(string),
    roles: array(string),
    joined_at: Js.Date.t,
    deaf: bool,
    mute: bool,
  };

  type unavailable = {
    id: string,
    unavailable: bool,
  };

  type t = {
    id: snowflake,
    name: string,
    icon: option(string),
    splash: option(string),
    owner: optional(bool),
    owner_id: snowflake,
    permissions: optional(int),
    region: string,
    afk_channel_id: option(snowflake),
    afk_timeout: int,
    embed_enabled: optional(bool),
    embed_channel_id: optional(snowflake),
    verification_level: int,
    default_message_notifications: int,
    explicit_content_filter: int,
    roles: array(Permissions.role),
    emojis: array(Emoji.t),
    features: array(string),
    mfa_level: int,
    application_id: option(snowflake),
    widget_enabled: optional(bool),
    widget_channel_id: optional(snowflake),
    system_channel_id: option(snowflake),
    joined_at: optional(Js.Date.t),
    large: optional(bool),
    unavailable: optional(bool),
    member_count: optional(int),
    voice_states: optional(array(Voice.state)),
    members: optional(array(member)),
    channels: optional(array(Channel.t)),
    presences: optional(array(Presence.update)),
    max_presences: optional(option(int)),
    max_members: optional(int),
    vanity_url_code: option(string),
    description: option(string),
    banner: option(string),
  };

  type create = t;
};

exception NotImplemented;

type updateStatus = {
  since: option(int),
  game: option(Presence.activity),
  status: string,
  afk: bool,
};

type ready = {
  v: int,
  user: User.t,
  private_channels: array(unit),
  guilds: array(Guild.unavailable),
  session_id: string,
  trace: array(string),
  shard: optional(array(int)),
};

type heartbeat = option(int);

type identify = {
  token: string,
  properties: props,
  compress: optional(bool),
  large_threshold: optional(int),
  shard: optional(array(int)),
  presence: optional(updateStatus),
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
  | Ready(ready)
  | GuildCreate(Guild.t);

type payload =
  | Event(event)
  | Heartbeat(heartbeat)
  | Identify(identify)
  | Hello(hello)
  | Ack;

type data = {
  op: int,
  d: payload,
  s: optional(int),
  t: optional(string),
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
    Field(
      switch (event) {
      | Ready(_) => "READY"
      | GuildCreate(_) => "GUILD_CREATE"
      },
    )
  | _ => Missing
  };

module Decode = {
  let optional_ = (decoder, json) =>
    switch (json |> Json.Decode.optional(decoder)) {
    | Some(x) => Field(x)
    | None => Missing
    };

  module Permissions = {
    open Permissions;

    let role = json =>
      Json.Decode.{
        id: json |> field("id", string),
        name: json |> field("name", string),
        color: json |> field("color", int),
        hoist: json |> field("hoist", bool),
        position: json |> field("position", int),
        permissions: json |> field("permissions", int),
        managed: json |> field("managed", bool),
        mentionable: json |> field("mentionable", bool),
      };
  };

  module User = {
    open User;

    let t = json =>
      Json.Decode.{
        id: json |> field("id", string),
        username: json |> field("username", string),
        discriminator: json |> field("discriminator", string),
        avatar: json |> field("avatar", optional(string)),
        bot: json |> field("bot", optional_(bool)),
        mfa_enabled: json |> optional_(field("mfa_enabled", bool)),
        locale: json |> optional_(field("locale", string)),
        verified: json |> optional_(field("verified", bool)),
        email: json |> optional_(field("email", string)),
        flags: json |> optional_(field("flags", int)),
        premium_type: json |> optional_(field("premium_type", int)),
      };
  };

  module Presence = {
    open Presence;

    let timestamps = json =>
      Json.Decode.{
        start: json |> optional_(field("start", int)),
        end_: json |> optional_(field("end", int)),
      };

    let party = json =>
      Json.Decode.{
        id: json |> optional_(field("id", string)),
        size: json |> optional_(field("size", array(int))),
      };

    let assets = json =>
      Json.Decode.{
        large_image: json |> optional_(field("large_image", string)),
        large_text: json |> optional_(field("large_text", string)),
        small_image: json |> optional_(field("small_image", string)),
        small_text: json |> optional_(field("small_text", string)),
      };

    let secrets = json =>
      Json.Decode.{
        join: json |> optional_(field("join", string)),
        spectate: json |> optional_(field("spectate", string)),
        match: json |> optional_(field("match", string)),
      };

    let activity = json =>
      Json.Decode.{
        name: json |> field("name", string),
        type_: json |> field("type", int),
        url: json |> optional_(field("url", optional(string))),
        timestamps: json |> optional_(field("timestamps", timestamps)),
        application_id: json |> optional_(field("application_id", string)),
        details: json |> optional_(field("details", optional(string))),
        state: json |> optional_(field("state", optional(string))),
        party: json |> optional_(field("party", party)),
        assets: json |> optional_(field("assets", assets)),
        secrets: json |> optional_(field("secrets", secrets)),
        instance: json |> optional_(field("instance", bool)),
        flags: json |> optional_(field("flags", int)),
      };

    let clientStatus = json =>
      Json.Decode.{
        desktop: json |> optional_(field("desktop", string)),
        mobile: json |> optional_(field("mobile", string)),
        web: json |> optional_(field("web", string)),
      };

    let update = json =>
      Json.Decode.{
        user: json |> field("user", User.t),
        roles: json |> field("roles", array(string)),
        game: json |> field("game", optional(activity)),
        guild_id: json |> field("guild_id", string),
        status: json |> field("status", string),
        activities: json |> field("activities", array(activity)),
        client_status: json |> field("client_status", clientStatus),
      };
  };

  module Channel = {
    open Channel;

    let overwrite = json =>
      Json.Decode.{
        id: json |> field("id", string),
        type_: json |> field("type", string),
        allow: json |> field("allow", int),
        deny: json |> field("deny", int),
      };

    let t = json =>
      Json.Decode.{
        id: json |> field("id", string),
        type_: json |> field("type", int),
        guild_id: json |> optional_(field("guild_id", string)),
        position: json |> optional_(field("position", int)),
        permission_overwrites:
          json
          |> optional_(field("permission_overwrites", array(overwrite))),
        name: json |> optional_(field("name", string)),
        topic: json |> optional_(field("topic", optional(string))),
        nsfw: json |> optional_(field("nsfw", bool)),
        last_message_id:
          json |> optional_(field("last_message_id", optional(string))),
        bitrate: json |> optional_(field("bitrate", int)),
        user_limit: json |> optional_(field("user_limit", int)),
        rate_limit_per_user:
          json |> optional_(field("rate_limit_per_user", int)),
        recipients: json |> optional_(field("recipients", array(User.t))),
        icon: json |> optional_(field("icon", optional(string))),
        owner_id: json |> optional_(field("owner_id", string)),
        application_id: json |> optional_(field("application_id", string)),
        parent_id: json |> optional_(field("parent_id", optional(string))),
        last_pin_timestamp:
          json |> optional_(field("last_pin_timestamp", date)),
      };
  };

  module Emoji = {
    open Emoji;

    let t = json =>
      Json.Decode.{
        id: json |> field("id", optional(string)),
        name: json |> field("name", string),
        roles: json |> optional_(field("roles", array(string))),
        user: json |> optional_(field("user", User.t)),
        require_colons: json |> optional_(field("require_colons", bool)),
        managed: json |> optional_(field("managed", bool)),
        animated: json |> optional_(field("animated", bool)),
      };
  };

  module rec Voice_: {let state: Js.Json.t => Voice.state;} = {
    open Voice;

    let state = json =>
      Json.Decode.{
        guild_id: json |> field("guild_id", string),
        channel_id: json |> field("channel_id", optional(string)),
        user_id: json |> field("user_id", string),
        member: json |> optional_(field("member", Guild_.member)),
      };
  }
  and Guild_: {
    let member: Js.Json.t => Guild.member;
    let unavailable: Js.Json.t => Guild.unavailable;
    let t: Js.Json.t => Guild.t;
    let create: Js.Json.t => Guild.create;
  } = {
    open Guild;

    let member = json =>
      Json.Decode.{
        user: json |> field("user", User.t),
        nick: json |> optional_(field("nick", string)),
        roles: json |> field("roles", array(string)),
        joined_at: json |> field("joined_at", date),
        deaf: json |> field("deaf", bool),
        mute: json |> field("mute", bool),
      };

    let unavailable = json =>
      Json.Decode.{
        id: json |> field("id", string),
        unavailable: json |> field("unavailable", bool),
      };

    let t = json =>
      Json.Decode.{
        id: json |> field("id", string),
        name: json |> field("name", string),
        icon: json |> field("icon", optional(string)),
        splash: json |> field("splash", optional(string)),
        owner: json |> optional_(field("owner", bool)),
        owner_id: json |> field("owner_id", string),
        permissions: json |> optional_(field("permissions", int)),
        region: json |> field("region", string),
        afk_channel_id: json |> field("afk_channel_id", optional(string)),
        afk_timeout: json |> field("afk_timeout", int),
        embed_enabled: json |> optional_(field("embed_enabled", bool)),
        embed_channel_id:
          json |> optional_(field("embed_channel_id", string)),
        verification_level: json |> field("verification_level", int),
        default_message_notifications:
          json |> field("default_message_notifications", int),
        explicit_content_filter:
          json |> field("explicit_content_filter", int),
        roles: json |> field("roles", array(Permissions.role)),
        emojis: json |> field("emojis", array(Emoji.t)),
        features: json |> field("features", array(string)),
        mfa_level: json |> field("mfa_level", int),
        application_id: json |> field("application_id", optional(string)),
        widget_enabled: json |> optional_(field("widget_enabled", bool)),
        widget_channel_id:
          json |> optional_(field("widget_channel_id", string)),
        system_channel_id:
          json |> field("system_channel_id", optional(string)),
        joined_at: json |> optional_(field("joined_at", date)),
        large: json |> optional_(field("large", bool)),
        unavailable: json |> optional_(field("unavailable", bool)),
        member_count: json |> optional_(field("member_count", int)),
        voice_states:
          json |> optional_(field("voice_states", array(Voice_.state))),
        members: json |> optional_(field("members", array(member))),
        channels: json |> optional_(field("channels", array(Channel.t))),
        presences:
          json |> optional_(field("presences", array(Presence.update))),
        max_presences:
          json |> optional_(field("max_presences", optional(int))),
        max_members: json |> optional_(field("max_members", int)),
        vanity_url_code: json |> field("vanity_url_code", optional(string)),
        description: json |> field("description", optional(string)),
        banner: json |> field("banner", optional(string)),
      };

    let create = t;
  };

  module Voice = Voice_;
  module Guild = Guild_;

  let ready = json =>
    Json.Decode.{
      v: json |> field("v", int),
      user: json |> field("user", User.t),
      private_channels: json |> field("private_channels", array(_ => ())),
      guilds: json |> field("guilds", array(Guild.unavailable)),
      session_id: json |> field("session_id", string),
      trace: json |> field("_trace", array(string)),
      shard: json |> optional_(field("shard", array(int))),
    };

  let hello = json =>
    Json.Decode.{
      heartbeat_interval: json |> field("heartbeat_interval", int),
      trace: json |> field("_trace", array(string)),
    };

  let data = json =>
    Json.Decode.{
      op: json |> field("op", int),
      d:
        json
        |> field("d", j =>
             switch (json |> field("op", int)) {
             | 0 =>
               Event(
                 switch (json |> field("t", string)) {
                 | "READY" => Ready(ready(j))
                 | "GUILD_CREATE" => GuildCreate(Guild.create(j))
                 | _ => raise(NotImplemented)
                 },
               )
             | 10 => Hello(hello(j))
             | 11 => Ack
             | _ => raise(NotImplemented)
             }
           ),

      s: json |> optional_(field("s", int)),
      t: json |> optional_(field("t", string)),
    };
};

module Encode = {
  let required = (encoder, r) => Field(encoder(r));

  let optional = (encoder, r) =>
    switch (r) {
    | Field(x) => Field(encoder(x))
    | Missing => Missing
    };

  let null_ = (encoder, r) =>
    switch (r) {
    | None => Json.Encode.null
    | Some(x) => encoder(x)
    };

  let object__ = fields =>
    List.fold_right(
      (b, a) =>
        switch (b) {
        | (str, Field(json)) => [(str, json), ...a]
        | (_, Missing) => a
        },
      fields,
      [],
    )
    |> Json.Encode.object_;

  module Presence = {
    open Presence;

    let timestamps = r =>
      Json.Encode.(
        object__([
          ("start", r.start |> optional(int)),
          ("end", r.end_ |> optional(int)),
        ])
      );

    let party = r =>
      Json.Encode.(
        object__([
          ("id", r.id |> optional(string)),
          ("size", r.size |> optional(array(int))),
        ])
      );

    let assets = r =>
      Json.Encode.(
        object__([
          ("large_image", r.large_image |> optional(string)),
          ("large_text", r.large_text |> optional(string)),
          ("small_image", r.small_image |> optional(string)),
          ("small_text", r.small_text |> optional(string)),
        ])
      );

    let secrets = r =>
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
          ("url", r.url |> optional(null_(string))),
          ("timestamps", r.timestamps |> optional(timestamps)),
          ("application_id", r.application_id |> optional(string)),
          ("details", r.details |> optional(null_(string))),
          ("state", r.state |> optional(null_(string))),
          ("party", r.party |> optional(party)),
          ("assets", r.assets |> optional(assets)),
          ("secrets", r.secrets |> optional(secrets)),
          ("instance", r.instance |> optional(bool)),
          ("flags", r.flags |> optional(int)),
        ])
      );
  };

  let updateStatus = r =>
    Json.Encode.(
      object__([
        ("since", r.since |> required(null_(int))),
        ("game", r.game |> required(null_(Presence.activity))),
        ("status", r.status |> required(string)),
        ("afk", r.afk |> required(bool)),
      ])
    );

  let heartbeat = null_(Json.Encode.int);

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

  let data = r =>
    Json.Encode.(
      object__([
        ("op", r.op |> required(int)),
        (
          "d",
          switch (r.d) {
          | Heartbeat(payload) => payload |> required(heartbeat)
          | Identify(payload) => payload |> required(identify)
          | _ => Missing
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
          | _ => Missing
          },
        ),
        ("t", t_of_payload(r) |> optional(string)),
      ])
    );
};