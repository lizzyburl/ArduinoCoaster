function[] =  plot_all_trials()
   
   TestCoasterSVM();
    
end


function [accuracy] = TestCoasterSVM()

    model = GetSVMModel();
    all_trials = [];
    for i = 9:1:11
        trial = load(sprintf('Trial_%d.dat', i));
        formatted_trial = Format_Trial_Data(trial);
        all_trials = vertcat(all_trials, formatted_trial);
    end

    addpath('windows');
    test_labels = all_trials(:,1);
    test_data = all_trials(:,2:5);

    tooHot = test_data(test_labels==1, :);
    tooCold = test_data(test_labels==-1, :);
    figure(2);
    plot(tooHot(:,2), tooHot(:,1), '.r', tooCold(:,2), tooCold(:,1), '.b');
    xlabel('Time (s)');
    ylabel('Temperature (F)');
    title('Testing True Labels: Temperature Under Cup As Time Increases');


    test_data = sparse(test_data);
    figure(3);
    [p_lab, accuracy, p_ests] = predict(test_labels, test_data, model);

    tooHot = test_data(p_lab==1, :);
    tooCold = test_data(p_lab==-1, :);
    plot(tooHot(:,2), tooHot(:,1), '.r', tooCold(:,2), tooCold(:,1), '.b');
    xlabel('Time (s)');
    ylabel('Temperature (F)');
    title('Testing Predicted Labels: Temperature Under Cup As Time Increases');
    
end

function [model] = GetSVMModel()

all_trials = [];
for i = 1:1:8
    trial = load(sprintf('Trial_%d.dat', i));
    formatted_trial = Format_Trial_Data(trial);
    all_trials = vertcat(all_trials, formatted_trial);
end

addpath('windows');
labels = all_trials(:,1);
data = all_trials(:,2:5);

tooHot = data(labels==1, :);
tooCold = data(labels==-1, :);

plot(tooHot(:,2), tooHot(:,1), '.r', tooCold(:,2), tooCold(:,1), '.b');
xlabel('Time (s)');
ylabel('Temperature (F)');
title('Training: Temperature Under Cup As Time Increases');
data = sparse(data);
model = train(labels, data);

save('model.mat', 'model');

end

function [trial_data] = Format_Trial_Data(trial)

    [rows, cols] = size(trial);
    trial_data = ones(rows, cols + 2);
    prev_temp = trial(1,2);
    for i = 1:5:rows
        if i+4 < rows
            avg_temp = mean(trial(i:i+4,2));
            trial_data(i:i+4,2) = repmat(avg_temp,1,5);
            delta_y = avg_temp - prev_temp;
            trial_data(i:i+4, 4) = repmat(delta_y, 1,5);
            prev_temp = avg_temp;
        end
    end
    trial_data(:,3) = trial(:,3);
    trial_data(:,1) = trial(:,1);
    times = trial(:,1);
end

