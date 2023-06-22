import socket

class Items:
    def __init__(self, client_socket:socket) -> None:
        self.client_socket:socket = client_socket
        
    def needsFood(self, inventory:list, ListFilled:list):
        try:
            if inventory["food"] < 5 and len(ListFilled) < 3:
                for i in range(3):
                    ListFilled.append("food")
        except KeyError:
            return

    def takeItem(self, sight:str, objectives:list, foodList:list, inventory:list) -> None:
        for i in range(len(objectives)):
            try:
                sight[0].index(objectives[i])
                self.client_socket.send(("Take " + objectives[i] + "\n").encode())
                self.client_socket.recv(1024)
                objectives.pop(i)
            except ValueError:
                continue
        try:
            if inventory["food"] >= 20:
                return
            sight[0].index("food")
            self.client_socket.send(("Take food\n").encode())
            self.client_socket.recv(1024)
            if (len(foodList) > 0):
                foodList.pop(0)
        except ValueError:
            return
        except KeyError:
            return
        
    def setItem(self, itemToSet:str, objectives:list) -> str:
        self.client_socket.send(("Set " + itemToSet + "\n").encode())
        objectives.append(itemToSet)
        return self.client_socket.recv(1024).decode()