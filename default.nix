let
  sources =  import ./nix/sources.nix;
  project_overlay = self: super: {
    cpp = self.callPackage ./nix/cpp.nix {};
  };

  pkgs = import sources.nixpkgs {
    overlays = [
      (_: _: {
        inherit sources;
        gitignoreSource = (import sources."gitignore" {}).gitignoreSource;
      })

      project_overlay
    ];
  };
in
with pkgs;

stdenv.mkDerivation {
  name = "cpp";
  nativeBuildInputs = [ niv cmake pkgconfig clang-tools ];
  src = gitignoreSource ./.;

  cmakeFlags = [
    "-DEXTERNAL_INCLUDE_DIRECTORIES=${stdenv.lib.strings.makeSearchPathOutput "dev" "include" cpp.buildInputs}"
  ];

  buildInputs = stdenv.lib.lists.concatLists [
    [ cpp.buildInputs ]
    [ cpp ]
  ];
}
