function res = calibration(vargin)
    cal_dist = [5:5:100];
    cal_read = [383 549 583 531 465 401 355 310 280 248 ...
        227 211 198 181 171 162 149 142 135 129];
    read_domain = [0:1:700];

    lookup = interp1(cal_read(3:end), cal_dist(3:end), read_domain);
    for i=[1:1:size(lookup,2)]
        if isnan(lookup(i))&&(i<size(lookup,2)/2)
            [val,index] = min(cal_read);
            lookup(i) = cal_dist(index);
        elseif isnan(lookup(i))
            [val,index] = max(cal_read);
            lookup(i) = cal_dist(index);
        end
    end

%     plot(lookup,'LineWidth',3);
%     title('IR Sensor Calibration','FontSize',16);
%     legend('Distance-Reading Relation','Location','NorthEast');
%     xlabel('Arduino Analog Reading','FontSize',14);
%     ylabel('Distance (cm)','FontSize',14);
%     set(gca, 'FontSize',12);

    if nargin<1
        reading = 1;
    else
        reading = vargin(1);
    end
    res = lookup(round(reading));
end