#!/usr/bin/env python3
import http.server
import os

class WasmHandler(http.server.SimpleHTTPRequestHandler):
    def do_GET(self):
        if self.path == "/" or self.path == "/index.html":
            self.path = "/game.html"
        return super().do_GET()

    def end_headers(self):
        self.send_header("Cross-Origin-Opener-Policy", "same-origin")
        self.send_header("Cross-Origin-Embedder-Policy", "require-corp")
        super().end_headers()

    def log_message(self, format, *args):
        pass

os.chdir("bin/wasm")
server = http.server.HTTPServer(("0.0.0.0", 5000), WasmHandler)
print("[WASM] Servidor WebAssembly na porta 5000", flush=True)
print("[WASM] Acesse: game.html", flush=True)
server.serve_forever()
