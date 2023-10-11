clear
clc

%% Irreduction Polynomials for m=163, 283, 571
poly163 = [7, 6, 3, 0];
poly283 = [12, 7, 5, 0];
poly571 = [10, 5, 2, 0];

%% Choose the field
m = 163;
poly = poly163;

%% Q Matrix Generation
a = zeros(1, m*m);
for i = 0:m-1
    if 2*i <= m-1
        a(i*m+1 +1) = 2*i;
        a(i*m+0 +1) = 1;
    elseif 2*i <= 2*m-1-poly(1)
        a(i*m+1 +1) = 2*i - m + poly(1);
        a(i*m+2 +1) = 2*i - m + poly(2);
        a(i*m+3 +1) = 2*i - m + poly(3);
        a(i*m+4 +1) = 2*i - m + poly(4);
        a(i*m+0 +1) = 4;
    elseif 2*i <= 2*m-1-poly(2)
        a(i*m+1 +1) = 2*i - m + poly(2);
        a(i*m+2 +1) = 2*i - m + poly(3);
        a(i*m+3 +1) = 2*i - m + poly(4);
        a(i*m+4 +1) = 2*i + poly(1) + poly(1) - 2*m;
        a(i*m+5 +1) = 2*i + poly(1) + poly(2) - 2*m;
        a(i*m+6 +1) = 2*i + poly(1) + poly(3) - 2*m;
        a(i*m+7 +1) = 2*i + poly(1) + poly(4) - 2*m;
        a(i*m+0 +1) = 7;
    elseif 2*i <= 2*m-1-poly(3)
        a(i*m+1 +1) = 2*i - m + poly(3);
        a(i*m+2 +1) = 2*i - m + poly(4);
        a(i*m+3 +1) = 2*i + poly(1) + poly(1) - 2*m;
        a(i*m+4 +1) = 2*i + poly(1) + poly(2) - 2*m;
        a(i*m+5 +1) = 2*i + poly(1) + poly(3) - 2*m;
        a(i*m+6 +1) = 2*i + poly(1) + poly(4) - 2*m;
        a(i*m+7 +1) = 2*i + poly(2) + poly(1) - 2*m;
        a(i*m+8 +1) = 2*i + poly(2) + poly(2) - 2*m;
        a(i*m+9 +1) = 2*i + poly(2) + poly(3) - 2*m;
        a(i*m+10 +1) = 2*i + poly(2) + poly(4) - 2*m;
        a(i*m+0 +1) = 10;
    else
        a(i*m+1 +1) = 2*i - m + poly(4);
        a(i*m+2 +1) = 2*i + poly(1) + poly(1) - 2*m;
        a(i*m+3 +1) = 2*i + poly(1) + poly(2) - 2*m;
        a(i*m+4 +1) = 2*i + poly(1) + poly(3) - 2*m;
        a(i*m+5 +1) = 2*i + poly(1) + poly(4) - 2*m;
        a(i*m+6 +1) = 2*i + poly(2) + poly(1) - 2*m;
        a(i*m+7 +1) = 2*i + poly(2) + poly(2) - 2*m;
        a(i*m+8 +1) = 2*i + poly(2) + poly(3) - 2*m;
        a(i*m+9 +1) = 2*i + poly(2) + poly(4) - 2*m;
        a(i*m+10 +1) = 2*i + poly(3) + poly(1) - 2*m;
        a(i*m+11 +1) = 2*i + poly(3) + poly(2) - 2*m;
        a(i*m+12 +1) = 2*i + poly(3) + poly(3) - 2*m;
        a(i*m+13 +1) = 2*i + poly(3) + poly(4) - 2*m;
        a(i*m+0 +1) = 13;
    end
    j = 1;
    while j <= a(i*m+0 +1)-1
        flag = 1;
        for k = (j+1):a(i*m+0 +1)
            if a(i*m+k +1) == a(i*m+j +1)
                for t = k:a(i*m+0 +1)
                    a(i*m+t +1) = a(i*m+t+1 +1);
                end
                a(i*m+0 +1) = a(i*m+0 +1) - 1;
                for t = j:a(i*m+0 +1)
                    a(i*m+t +1) = a(i*m+t+1 +1);
                end
                a(i*m+0 +1) = a(i*m+0 +1) - 1;
                flag = 0;
            end
            if flag == 0
                break;
            end
        end
        if flag == 0
            j = j - 1;
        end
        j = j + 1;
    end

end

temp = zeros(1,m*m);
for i = 0:m-1
    for j = 1:a(i*m+0 +1)
        p = a(i*m+j +1);
        q = temp(p*m+0 +1);
        temp(p*m+q+1 +1) = i;
        temp(p*m+0 +1) = temp(p*m+0 +1) + 1;
    end
end

Q = zeros(m, m);
for i = 0:m-1
    for j = 1:temp(i*m+0 +1)
        Q(i+1, temp(i*m+j +1) +1) = 1;
    end
end

%% Q Matrix Accumulation
b = zeros(1,m);
QQ = Q;
b(1) = sum(sum(Q));
for k = 2:m
    QQ = QQ * Q;
    QQ = mod(QQ, 2);
    b(k) = sum(sum(QQ));
end

%% Plot
figure;
x = (1:m);
y = b;
plot(x, y);

xlabel('Number of SQRs', 'Fontname', 'Times New Roman');
ylabel('Weight of Q^e', 'Fontname', 'Times New Roman');