format long

origo = [3,3];

nledsy = 5;
nledsx = 5;

l_eye_rad = zeros(nledsy,nledsx);

for l = 1:nledsy
  for k = 1:nledsx
    l_eye_rad(l,k) = abs(l-origo(1) + j* (k-origo(2)));
  end
end

max_dist = max(max(l_eye_rad))

radius_to_origo = floor((l_eye_rad./max_dist) * 2^32)

# angle calc

l_eye_ang = zeros(nledsy,nledsx);

for l = 1:nledsy
  for k = 1:nledsx
    l_eye_ang(l,k) = angle(l-origo(1)+ -j * (k-origo(2)) );
  end
end

l_eye_ang = l_eye_ang + pi;

round(l_eye_ang./(2*pi)*2^32)