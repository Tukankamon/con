{
  inputs.nixpkgs.url = "nixpkgs/nixos-unstable";
  outputs = {self, nixpkgs}:
    let
      pkgs = nixpkgs.legacyPackages.x86_64-linux;
    in {
      devShells."x86_64-linux".default = pkgs.mkShell {
        buildInputs = with pkgs; [
          fish cargo rustc rustfmt
        ];
        shellHook = ''
          fish
        '';
      };
    };
}
