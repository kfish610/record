type user = {
  id: string,
  username: string,
  discriminator: string,
  avatar: Js.null(string),
  bot: option(bool),
  mfa_enabled: option(bool),
  locale: option(string),
  verified: option(bool),
  email: option(string),
  flags: option(int),
  premium_type: option(int)
};