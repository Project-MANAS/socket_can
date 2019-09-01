#include <socket_can/socket_can.hpp>

namespace socket_can
{
SocketCAN::SocketCAN() :
  connected_(false)
{
  init();
}

SocketCAN::~SocketCAN()
{
  if (close(socket_) < 0) {
    perror("Closing: ");
    printf("Error: %d", errno);
  }
}

void SocketCAN::init()
{
  if((socket_ = socket(PF_CAN, SOCK_RAW, CAN_RAW)) < 0) {
    perror("Error while opening socket");
    return;
  }

  struct ifreq ifr{};
  const char * ifname = "vcan0";
  strcpy(ifr.ifr_name, ifname);
  ioctl(socket_, SIOCGIFINDEX, &ifr);

  struct sockaddr_can addr{};
  addr.can_family  = AF_CAN;
  addr.can_ifindex = ifr.ifr_ifindex;

  printf("%s at index %d\n", ifname, ifr.ifr_ifindex);

  if(bind(socket_, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
    perror("Error in socket bind");
    return;
  }

  connected_ = true;
}

bool SocketCAN::is_connected()
{
  return connected_;
}

bool SocketCAN::write(uint32_t can_id, uint8_t dlc, uint8_t * data)
{
  struct can_frame frame{};

  frame.can_id  = can_id;
  frame.can_dlc = dlc;
  memcpy(frame.data, data, dlc * sizeof(uint8_t));

  auto num_bytes = ::write(socket_, &frame, sizeof(struct can_frame));

  return num_bytes > 0;
}

bool SocketCAN::read(size_t size, uint8_t * data)
{
  struct can_frame frame{};
  auto num_bytes = ::read(socket_, &frame, size);
  if (num_bytes != size) {
    return false;
  }
  memcpy(data, frame.data, sizeof(size));
  return true;
}
}