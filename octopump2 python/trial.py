while 1:
    command = str(input('Enter in Command'))
    if command == 'end':
        raise SystemExit(0)
    else:
        command = command.encode()
        arduino.write(command)
        while exit != 0:
            exit = arduino.readline()
            exit = exit.decode()
            try:
                exit = int(exit)
            except:
                exit = 1
        print('done')