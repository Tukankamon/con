Simple number converter for quick terminal conversions

Written in C because I was getting rusty ;) in it

# Usage
```
Usage: bin/main 0x/0b/0o + NUMBER [-b] [-x] [-d] [-o]

-b to output to binary
-d to output to decimal
-x to output to hexadecimal
-o to output to octal
-h to show this page
```

# Nix
Add the following to your configuration:
(Change the rev to whatever commit you want)
```nix
environment.systemPackages = [
    (pkgs.stdenv.mkDerivation (finalAttrs: {
      pname = "con";
      version = "0.0.1";
      NIX_CFLAGS_COMPILE = "-w";
      src = pkgs.fetchFromGitHub {
        owner = "Tukankamon";
        repo = "con";
        rev = "main"; # Or just the commit has
        #rev = "v.${finalAttrs.version}";
        hash = "sha256-zBg9qF43YLYK+KRC5ph3LOaCT//kl/PLV4ugr5AH5WE=";
      };
      installPhase = ''
        mkdir -p $out/bin
        cp bin/con $out/bin/
      '';
    }))
];
```
Hash might be different
