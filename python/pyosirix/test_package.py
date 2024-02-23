# from testpyosirix import Osirix, OsirixService
# from testpyosirix import Osirix
# import sys
# print(sys.path)
# sys.path.append("/Users/admintmun/.pyenv/versions/3.7.8/envs/test/lib/python3.7/site-packages")
if __name__ == '__main__':
    port = 50051
    domain = "localhost:"
    # address
    channel_opt = [('grpc.max_send_message_length', 512 * 1024 * 1024),
                   ('grpc.max_receive_message_length', 512 * 1024 * 1024)]
    #
    # osirix_service = OsirixService(channel_opt=channel_opt, domain=domain, port=port).get_service()
    # pyosirix = Osirix(osirix_service)
    #
    # browser_controller = pyosirix.current_browser()
    # # vr_controller = pyosirix.frontmost_vr_controller()
    # viewer_controller = pyosirix.frontmost_viewer()
    # print(viewer_controller.modality)
    # print(viewer_controller.cur_dcm().source_file)
