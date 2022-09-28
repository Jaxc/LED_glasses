origo = [4,4.5];

l_eye_rad = zeros(7,8);

for l = 1:7
  for k = 1:8
    l_eye_rad(l,k) = abs(l-origo(1) + j* (k-origo(2)));
  end
end

# Remove values with no corresponding led
l_eye_rad(1,1) = 0;
l_eye_rad(1,2) = 0;
l_eye_rad(2,1) = 0;
l_eye_rad(5,1) = 0;
l_eye_rad(6,1) = 0;
l_eye_rad(7,1) = 0;
l_eye_rad(7,2) = 0;
l_eye_rad(5,8) = 0;
l_eye_rad(6,7) = 0;
l_eye_rad(6,8) = 0;
l_eye_rad(7,6) = 0;
l_eye_rad(7,7) = 0;
l_eye_rad(7,8) = 0;

max_dist = max(max(l_eye_rad))

uint_32_values = floor((l_eye_rad./max_dist) * 2^32)

# angle calc

l_eye_ang = zeros(7,8);

for l = 1:7
  for k = 1:8
    l_eye_ang(l,k) = angle(l-origo(1)+ -j * (k-origo(2)) );
  end
end

l_eye_ang = l_eye_ang + pi;

l_eye_ang(1,1) = 0;
l_eye_ang(1,2) = 0;
l_eye_ang(2,1) = 0;
l_eye_ang(5,1) = 0;
l_eye_ang(6,1) = 0;
l_eye_ang(7,1) = 0;
l_eye_ang(7,2) = 0;
l_eye_ang(5,8) = 0;
l_eye_ang(6,7) = 0;
l_eye_ang(6,8) = 0;
l_eye_ang(7,6) = 0;
l_eye_ang(7,7) = 0;
l_eye_ang(7,8) = 0;

round(l_eye_ang./(2*pi)*2^32)