from cryptography.fernet import Fernet
import secrets

def str_to_bytes(s):
    return bytes(s, 'utf-8')


def encrypt(key, message):
    f = Fernet(key)
    if type(message) is str:
        message = str_to_bytes(message)
    return f.encrypt(message)


def decrypt(key, message):
    f = Fernet(key)
    if type(message) is str:
        message = str_to_bytes(message)
    return f.decrypt(message)


class AuthServer:
    def __init__(self):
        self.passwords = {}

    def add_pass(self, id, password):
        self.passwords[id] = password
    
    def get_tgs_ticket(self, id):
        client_tgs = encrypt(self.passwords[id], self.passwords[id])
        verif = encrypt(self.passwords['tgs'], str_to_bytes(self.passwords[id].decode('utf-8') + ' ' + id))
        return client_tgs, verif


class TicketGrantingServer:
    def __init__(self, as_tgs):
        self.as_tgs = as_tgs
        self.keys = {}

    def add_server_key(self, id, key):
        self.keys[id] = key

    def get_access(self, en_id, en_verif, server_id):
        verif = decrypt(self.as_tgs, en_verif)
        verif_strings = verif.decode('utf-8').split()

        client_tgs = str_to_bytes(verif_strings[0])
        verif_id = str_to_bytes(verif_strings[1])

        client_id = decrypt(client_tgs, en_id)

        if not secrets.compare_digest(client_id, verif_id):
            return
        
        client_server = Fernet.generate_key()
        en_client_server = encrypt(client_tgs, client_server)
        verif_for_server = encrypt(self.keys[server_id], str_to_bytes(client_server.decode('utf-8') + ' ' + client_id.decode('utf-8')))
        return en_client_server, verif_for_server


class Server:
    def __init__(self):
        self.server_tgs = Fernet.generate_key()
        tgs.add_server_key('server', self.server_tgs)
        self.keys = {}
        
    def initiate(self, en_id, en_verif, nr):
        verif = decrypt(self.server_tgs, en_verif)
        verif_strings = verif.decode('utf-8').split()

        client_server = str_to_bytes(verif_strings[0])
        verif_id = str_to_bytes(verif_strings[1])

        client_id = decrypt(client_server, en_id)

        if not secrets.compare_digest(client_id, verif_id):
            return

        self.keys[client_id] = client_server
        return nr + 1


def init ():
    global auth_s
    global tgs
    global server

    auth_s = AuthServer()
    as_tgs = Fernet.generate_key()
    tgs = TicketGrantingServer(as_tgs)
    auth_s.add_pass('tgs', as_tgs)

    server = Server()

def main(): 
    init()

    global auth_s
    global tgs
    global server

    client_pass = Fernet.generate_key()
    auth_s.add_pass('client', client_pass)

    en_client_tgs, en_verif = auth_s.get_tgs_ticket('client')
    client_tgs = decrypt(client_pass, en_client_tgs)
    en_id = encrypt(client_tgs, 'client')

    en_client_server, en_verif_for_server = tgs.get_access(en_id, en_verif, 'server')
    client_server = decrypt(client_pass, en_client_server)
    en_id = encrypt(client_server, 'client')
    
    print(server.initiate(en_id, en_verif_for_server, 1337))


if __name__ == '__main__':
    main()
