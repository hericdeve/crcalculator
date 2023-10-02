pkgname=crcalculator
pkgver=1.0.0
pkgrel=1
pkgdesc="A tool for managing grades"
arch=('i686' 'x86_64')
url="https://github.com/hericdeve/crcalculator.git"
license=('GPL')
depends=('gcc-libs')
makedepends=('gcc' 'git' 'cmake')
source=("git+$url")
md5sums=('SKIP')

build() {
  cd "$srcdir/$pkgname"
  chmod +x build.sh
  ./build.sh
}

package() {
  cd "$srcdir/$pkgname/build"
  install -Dm755 crcalculator "$pkgdir/usr/bin/crcalculator"
}
