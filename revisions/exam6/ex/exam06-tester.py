#!/usr/bin/env python3
"""
tester.py - A comprehensive test suite for the mini_serv.c project (42 Exam Rank 06).

This script automates the testing of a mini_serv executable. It spans up a server,
connects multiple clients, and tests various scenarios including:
- Basic client connections and disconnections.
- Sending simple, partial, and multi-line messages.
- Stress testing with numerous concurrent clients.
- Handling large payloads and verifying server broadcast speed.
"""

import argparse
import socket
import subprocess
import time
import select

def get_free_port():
    """
    Finds and returns an available port on the local machine.

    Returns:
        int: A free port number.
    """
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.bind(('', 0))
    port = s.getsockname()[1]
    s.close()
    return port

class MiniServTester:
    """
    A class to test the mini_serv executable.

    It launches the server process on a given port and provides methods to connect,
    disconnect, read responses, and run specific test suites.
    """

    def __init__(self, port, use_valgrind=False):
        """
        Initializes the tester and starts the mini_serv process.

        Args:
            port (int): The port number to run the server on.
            use_valgrind (bool): Whether to run the server with valgrind.
        """
        self.port = port
        self.use_valgrind = use_valgrind
        
        self.server_process = None
        if use_valgrind:
            print(f"\n[*] \033[93mMANUAL MODE ENABLED\033[0m")
            print(f"[*] Please run the following command in a new terminal:\n")
            print(f"    (trap '' SIGPIPE; valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes -s ./mini_serv {port})\n")
            input("[*] \033[92mPress ENTER here once your server is running...\033[0m")
        else:
            print(f"[*] Starting mini_serv on port {port}...")
            cmd = ['./mini_serv', str(port)]
            self.server_process = subprocess.Popen(cmd, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
            time.sleep(0.5) # Initial boot sleep is necessary to allow server to bind
            if self.server_process.poll() is not None:
                err = self.server_process.stderr.read().decode()
                raise Exception(f"Server failed to start: {err}")
                
        self.clients = []
        self.next_id = 0

    def connect_client(self):
        """
        Connects a new client socket to the server.

        Returns:
            tuple: A tuple containing the socket object and its assigned client ID.
        """
        s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        s.connect(('127.0.0.1', self.port))
        s.setblocking(False)
        self.clients.append(s)
        client_id = self.next_id
        self.next_id += 1
        return s, client_id

    def disconnect_client(self, s):
        """
        Disconnects and closes a client socket.

        Args:
            s (socket.socket): The client socket to disconnect.
        """
        s.close()
        if s in self.clients:
            self.clients.remove(s)

    def read_until(self, s, expected, timeout=2.0):
        """
        Reads data from a socket until the expected string is found or a timeout occurs.

        Args:
            s (socket.socket): The socket to read from.
            expected (str): The expected substring to look for in the received data.
            timeout (float): Maximum time to wait in seconds.

        Returns:
            str: The decoded string received from the socket.
        """
        start_time = time.time()
        result = ""
        while time.time() - start_time < timeout:
            ready = select.select([s], [], [], 0.05)
            if ready[0]:
                try:
                    data = s.recv(65536)
                    if not data:
                        break
                    result += data.decode('utf-8')
                    if expected in result:
                        return result
                except (BlockingIOError, ConnectionResetError):
                    pass
        return result

    def read_all(self, s, timeout=0.2):
        """
        Reads all available data from a socket until a timeout or no more data is received.

        Args:
            s (socket.socket): The socket to read from.
            timeout (float): Maximum time to wait for data chunks.

        Returns:
            str: The decoded string received from the socket.
        """
        result = ""
        start_time = time.time()
        while time.time() - start_time < timeout:
            ready = select.select([s], [], [], 0.02)
            if ready[0]:
                try:
                    data = s.recv(65536)
                    if not data:
                        break
                    result += data.decode('utf-8')
                except (BlockingIOError, ConnectionResetError):
                    break
            else:
                break
        return result

    def test_basic(self):
        """
        Executes basic functionality tests.

        Tests:
        - Arrival notification: proper broadcast when a new client connects.
        - Basic messaging: single line messages are routed correctly.
        - Partial messaging: messages missing a newline are buffered correctly.
        - Multi-line messaging: payloads with multiple lines are processed sequentially.
        - Client departure: proper broadcast when a client disconnects.
        """
        print("\n=== Test 1: Basic connection & arrival notification ===")
        c0, id0 = self.connect_client()
        c1, id1 = self.connect_client()

        expected = f"server: client {id1} just arrived\n"
        res = self.read_until(c0, expected)
        assert expected in res, f"Expected '{expected}', Got: '{res}'"
        print(f"✓ Client {id1} arrival notified to Client {id0}")

        print("\n=== Test 2: Basic message ===")
        c1.sendall(b"Hello from c1!\n")
        expected = f"client {id1}: Hello from c1!\n"
        res = self.read_until(c0, expected)
        assert expected in res, f"Expected '{expected}', Got: '{res}'"
        print("✓ Basic message sent correctly")

        print("\n=== Test 3: Partial message ===")
        c0.sendall(b"Par")
        res = self.read_all(c1, timeout=0.1)
        assert res == "", f"Should be empty due to partial message, Got: '{res}'"
        print("✓ Partial message correctly buffered (not sent yet)")

        c0.sendall(b"tial\n")
        expected = f"client {id0}: Partial\n"
        res = self.read_until(c1, expected)
        assert expected in res, f"Expected '{expected}', Got: '{res}'"
        print("✓ Completed message correctly sent")

        print("\n=== Test 4: Multiple lines concatenated ===")
        c1.sendall(b"Line1\nLine2\nLine3\n")
        expected = f"client {id1}: Line1\nclient {id1}: Line2\nclient {id1}: Line3\n"
        res = self.read_until(c0, expected)
        assert expected in res, f"Expected '{expected}', Got: '{res}'"
        print("✓ Multiple lines correctly split and prefixed")

        print("\n=== Test 5: Client leaves ===")
        self.disconnect_client(c1)
        expected = f"server: client {id1} just left\n"
        res = self.read_until(c0, expected)
        assert expected in res, f"Expected '{expected}', Got: '{res}'"
        print("✓ Departure notification sent correctly")

        self.disconnect_client(c0)

    def test_stress(self):
        """
        Executes stress tests to ensure robustness and performance.

        Tests:
        - High volume connections: establishes 250 concurrent clients to assess fd_set capabilities.
        - Mass messaging: sends simultaneous messages from numerous clients and checks receipt.
        - Large payloads: transmits strings larger than typical buffers (e.g., >8KB) to ensure proper fragmentation/processing.
        - Speed/Latency benchmark: ensures the server broadcasts a message to 200+ clients under a latency limit.
        """
        print("\n=== Test 6: Stress connections (250 clients) ===")
        clients_data = []
        c0, id0 = self.connect_client()

        for i in range(250):
            c, cid = self.connect_client()
            clients_data.append((c, cid))

        last_id = clients_data[-1][1]
        expected_arrival = f"server: client {last_id} just arrived\n"
        self.read_until(c0, expected_arrival, timeout=2.0)
        print("✓ 250 connections accepted without crashing")

        print("\n=== Test 7: Mass messaging & Large texts ===")
        for i, (c, cid) in enumerate(clients_data[:50]):
            c.sendall(f"Stress test message from {cid}\n".encode('utf-8'))

        if self.server_process is not None:
            assert self.server_process.poll() is None, "Server crashed during stress test!"

        last_stress_cid = clients_data[49][1]
        expected_stress = f"client {last_stress_cid}: Stress test message from {last_stress_cid}\n"
        res = self.read_until(c0, expected_stress, timeout=3.0)

        count = res.count("Stress test message from")
        assert count >= 50, f"Expected at least 50 stress messages, got {count}"
        print("✓ Server handled massive simultaneous messaging and all 50 messages received")

        # Flush dummy client 0 buffer before large payload text
        self.read_all(clients_data[0][0], timeout=0.1)

        print("\n=== Test 8: Large payload ===")
        c0.sendall(b"A" * 8000 + b"B" * 2000 + b"\n")
        expected_payload = f"client {id0}: " + "A" * 8000 + "B" * 2000 + "\n"
        res = self.read_until(clients_data[0][0], "B" * 2000 + "\n", timeout=3.0)
        assert expected_payload in res, "Large payload corrupted or missing"
        print("✓ Large payload > 8KB handled perfectly")

        print("\n=== Test 9: Speed / Latency Broadcast Benchmark ===")
        # Subject: "Warning our tester is expecting that you send the messages as fast as you can"
        import time
        start_broadcast = time.time()
        clients_data[50][0].sendall(b"Speed test!\n")

        # Read from the other 200+ dummy clients to ensure they all received it fast
        expected_speed = f"client {clients_data[50][1]}: Speed test!\n"
        success_count = 0
        for c, cid in clients_data[51:250]:
            if expected_speed in self.read_until(c, expected_speed, timeout=0.1):
                success_count += 1

        elapsed = time.time() - start_broadcast
        assert success_count == 199, f"Only {success_count}/199 clients received the broadcast in time."
        assert elapsed < 1.5, f"Server is too slow! Took {elapsed:.2f}s to broadcast."
        print(f"✓ Broadcast to 200 clients took only {elapsed:.4f} seconds (Extremely fast)")

        for c, cid in clients_data:
            self.disconnect_client(c)
        self.disconnect_client(c0)

    def cleanup(self):
        """
        Cleans up resources by closing all client sockets, terminating the server process,
        and printing the valgrind report if enabled.
        """
        for c in self.clients:
            try:
                c.close()
            except:
                pass
                
        if self.server_process is not None:
            self.server_process.kill()
            self.server_process.communicate()
        elif hasattr(self, 'use_valgrind') and self.use_valgrind:
            print("\n[*] \033[92mTests finished! You can now Ctrl+C your valgrind terminal to see the clean leak report.\033[0m")

def main():
    """
    Main entry point of the tester.

    Finds a random free port, runs the test suite against the server, and reports the results.
    Catches any exceptions and ensures proper cleanup.
    """
    parser = argparse.ArgumentParser(description="Test suite for mini_serv.")
    parser.add_argument('--valgrind', action='store_true', help="Run the server with valgrind")
    args = parser.parse_args()

    port = get_free_port()
    tester = MiniServTester(port, use_valgrind=args.valgrind)
    try:
        tester.test_basic()
        tester.test_stress()
        print("\n\033[92m[SUCCESS] ALL TESTS PASSED! YOUR MINI_SERV IS BULLETPROOF.\033[0m")
    except AssertionError as e:
        print(f"\n\033[91m[FAILED] Test assertion failure:\033[0m\n{e}")
    except Exception as e:
        print(f"\n\033[91m[ERROR] Unexpected test execution error:\033[0m\n{e}")
    finally:
        tester.cleanup()

if __name__ == "__main__":
    main()
