# Maintainer: Sava Majic <majicsava@gmail.com>
pkgname=easyencrypt
pkgver=1.0
pkgrel=1
pkgdesc="A simple AES encryption/decryption tool using Crypto++"
arch=('x86_64')
url="https://github.com/majicsava4/easyencrypt"
license=('MIT')
depends=('crypto++')
source=("main.cpp")
md5sums=('SKIP') 

build() {
    cd "$srcdir"
    g++ -std=c++11 -Wall -O2 main.cpp -lcryptopp -o easyencrypt
}

package() {
    cd "$srcdir"
    install -Dm755 easyencrypt "$pkgdir"/usr/bin/easyencrypt
}
