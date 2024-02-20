#!/usr/bin/python
import mido

# The NOTE ON message is structured as follows:
#
#     Status byte : 1001 CCCC
#     Data byte 1 : 0PPP PPPP
#     Data byte 2 : 0VVV VVVV
#
# where:
# "CCCC" is the MIDI channel (from 0 to 15)
# "PPP PPPP" is the pitch value (from 0 to 127)
# "VVV VVVV" is the velocity value (from 0 to 127)


midi_msg = mido.Message('note_on', note=60)

midi_msg_list = [midi_msg]

bps = 31250
num_databits = 8
parity = 'n'
num_stopbits = 1
lvl_0 = 3.0
lvl_1 = 0.0


out = oldout = 0
time = 0.0
timestep = 1.0 / bps
risetime = falltime = timestep / 20.0
idletime = timestep * (num_databits + 3)


def do_timestep(output, step, write_fn):
    global time
    global out, oldout
    global lvl_0, lvl_1

    out = output
    time_diff = 0

    if oldout != out:
        if oldout > out:
            # fall
            time_diff = falltime
        else:
            # rise
            time_diff = risetime
        lvl = (lvl_0 if oldout == 0 else lvl_1)
        write_fn("{0:g} {1:g}".format(time, lvl))
        lvl = (lvl_0 if out == 0 else lvl_1)
        write_fn("{0:g} {1:g}".format((time + time_diff), lvl))

        oldout = out

    time += step
    return time


if __name__ == "__main__":
    with open('pwl.midi_stream.txt', 'w') as out_file:

        def append_pwl_tuple(x):
            out_file.write(x)
            out_file.write('\n')

        do_timestep(0, 0, append_pwl_tuple)

        # idle
        do_timestep(0, idletime, append_pwl_tuple)

        for midi_msg in midi_msg_list:
            # start bit
            out = 1
            do_timestep(out, timestep, append_pwl_tuple)

            for msg_byte in midi_msg.bytes():

                # print("# {}").format(char);
                par = 0

                for bit in range(0, num_databits):
                    out = (msg_byte >> bit) & 1
                    par = bool(parity) ^ bool(out)

                    do_timestep(out, timestep, append_pwl_tuple)

                if parity == 'e':
                    # even parity
                    out = par
                elif parity == 'o':
                    # odd parity
                    out = ~par
                do_timestep(out, timestep, append_pwl_tuple)

                # stop bits
                out = 0
                do_timestep(out, (timestep * num_stopbits), append_pwl_tuple)

            # idle
            out = 0
            do_timestep(out, idletime, append_pwl_tuple)
