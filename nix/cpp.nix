{ stdenv, cmake, pkgconfig, boost, sources }:

stdenv.mkDerivation {
  src = sources.cpp;
  name = "cpp";
  nativeBuildInputs = [cmake pkgconfig];
  buildInputs = [ boost ];
}
