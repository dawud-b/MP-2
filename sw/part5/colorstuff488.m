
imgBuffer = imread("sample_1920x1080.bmp");

imshow(imgBuffer)

size(imgBuffer)

% [row, column, color]

for row = 1:1080
    for col = 1:1920

        if mod(row, 2) == 1 && mod(col, 2) == 1
             imgBuffer(row, col, :) = [imgBuffer(row, col, 1), 0, 0];
        end

        if mod(row, 2) == 1 && mod(col, 2) == 0
            imgBuffer(row, col, :) = [0, imgBuffer(row, col, 2), 0];            
        end
        
        if mod(row, 2) == 0 && mod(col, 2) == 1
            imgBuffer(row, col, :) = [0, imgBuffer(row, col, 2), 0]; 
        end

        if mod(row, 2) == 0 && mod(col, 2) == 0

            imgBuffer(row, col, :) = [0, 0, imgBuffer(row, col, 3)]; 
        end

    end
end

imshow(imgBuffer)

imwrite(imgBuffer, "bayer_image.bmp")

% Demosaicing

kernel3by3 = zeros(1, 9, 'uint32');

for row = 1:1080
    for col = 1:1920
        
        if row == 1 || col == 1
            kernel3by3(1) = 0;
        else
            kernel3by3(1) = max(imgBuffer(row-1, col-1, :));
        end
        
        if row == 1
            kernel3by3(2) = 0;
        else
            kernel3by3(2) = max(imgBuffer(row-1, col, :));
        end

        if row == 1 || col == 1920
            kernel3by3(3) = 0;
        else
            kernel3by3(3) = max(imgBuffer(row-1, col+1, :));
        end

        if col == 1
            kernel3by3(4) = 0;
        else
            kernel3by3(4) = max(imgBuffer(row, col-1, :));
        end

        kernel3by3(5) = max(imgBuffer(row, col, :));

        if col == 1920
            kernel3by3(6) = 0;
        else
            kernel3by3(6) = max(imgBuffer(row, col+1, :));
        end

        if row == 1080 || col == 1
            kernel3by3(7) = 0;
        else
            kernel3by3(7) = max(imgBuffer(row+1, col-1, :));
        end

        if row == 1080
            kernel3by3(8) = 0;
        else
            kernel3by3(8) = max(imgBuffer(row+1, col, :));
        end

        if row == 1080 || col == 1920
            kernel3by3(9) = 0;
        else
            kernel3by3(9) = max(imgBuffer(row+1, col+1, :));
        end

        red = 0;
        green = 0;
        blue = 0;

        if mod(row, 2) == 1 && mod(col, 2) == 1
            red = kernel3by3(5);
            green = idivide(kernel3by3(2) + kernel3by3(4) + kernel3by3(6) + kernel3by3(8), 4);
            blue = idivide(kernel3by3(1) + kernel3by3(3) + kernel3by3(7) + kernel3by3(9), 4);
        elseif mod(row, 2) == 1
            blue = idivide(kernel3by3(2) + kernel3by3(8), 2);
            red = idivide(kernel3by3(4) + kernel3by3(6), 2);
            green = idivide(kernel3by3(1) + kernel3by3(3) + kernel3by3(5) + kernel3by3(7) + kernel3by3(9), 5);            
        elseif mod(col, 2) == 1
            red = idivide(kernel3by3(2) + kernel3by3(8), 2);
            blue = idivide(kernel3by3(4) + kernel3by3(6), 2);
            green = idivide(kernel3by3(1) + kernel3by3(3) + kernel3by3(5) + kernel3by3(7) + kernel3by3(9), 5);
        else
            red = idivide(kernel3by3(1) + kernel3by3(3) + kernel3by3(7) + kernel3by3(9), 4);
            blue = kernel3by3(5);
            green = idivide(kernel3by3(2) + kernel3by3(4) + kernel3by3(6) + kernel3by3(8), 4);
        end

        imgBuffer(row, col, 1) = red;
        imgBuffer(row, col, 2) = green;
        imgBuffer(row, col, 3) = blue;

    end
end

imshow(imgBuffer)
imwrite(imgBuffer, "de-bayered_image.bmp")
