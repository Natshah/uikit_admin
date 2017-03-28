<?php

/**
 * @file
 * Implements theme_status_report().
 */
?>

<div id="status-report-counters" class="uk-grid" data-uk-grid-match>

  <?php if ($errors): ?>
    <div id="status-report-counter-errors" class="status-report-counter <?php print $status_counters['grid_width']; ?>">
      <div class="uk-panel uk-panel-box" style="height: 55px">
        <i class="uk-icon-times-circle uk-icon-large uk-text-danger status-report-counter-icon"></i>
        <h3 class="uk-panel-title"><?php print $status_counters['error']['count']; ?> <?php print $status_counters['error']['title']; ?></h3>
        <div class="uk-width-1-1 uk-float-left uk-margin-large-left uk-clearfix">
          <a href="#errors">Details</a>
        </div>
      </div>
    </div>
  <?php endif; ?>

  <?php if ($warnings): ?>
    <div id="status-report-counter-warnings" class="status-report-counter <?php print $status_counters['grid_width']; ?>">
      <div class="uk-panel uk-panel-box" style="height: 55px">
        <i class="uk-icon-exclamation-triangle uk-icon-large uk-text-warning status-report-counter-icon"></i>
        <h3 class="uk-panel-title"><?php print $status_counters['warning']['count']; ?> <?php print $status_counters['warning']['title']; ?></h3>
        <div class="uk-width-1-1 uk-float-left uk-margin-large-left uk-clearfix">
          <a href="#warnings">Details</a>
        </div>
      </div>
    </div>
  <?php endif; ?>

  <div id="status-report-counter-checked" class="status-report-counter <?php print $status_counters['grid_width']; ?>">
    <div class="uk-panel uk-panel-box" style="height: 55px">
      <i class="uk-icon-check uk-icon-large uk-text-success status-report-counter-icon"></i>
      <h3 class="uk-panel-title"><?php print $status_counters['checked']['count']; ?> <?php print $status_counters['checked']['title']; ?></h3>
      <div class="uk-width-1-1 uk-float-left uk-margin-large-left uk-clearfix">
        <a href="#checked">Details</a>
      </div>
    </div>
  </div>

</div>

<div id="status-report-general-information" class="uk-grid">
  <div class="uk-width-1-1">
    <div class="uk-panel uk-panel-box uk-panel-header">
      <h3 class="uk-panel-title uk-text-bold uk-text-uppercase">General System Information</h3>

      <div class="uk-grid uk-margin-bottom">
        <div class="uk-width-small-1-1 uk-width-medium-1-3 uk-margin-bottom">
          <i class="uk-icon-drupal uk-icon-large uk-text-muted uk-width-1-5 uk-width-medium-1-10 uk-float-left uk-admin-vertical-align-top"></i>
          <div class="uk-width-4-5 uk-width-medium-9-10 uk-float-left">
            <h3 class="uk-text-bold uk-margin-small-bottom">Drupal</h3>
            <h4 class="uk-margin-small-top uk-margin-bottom-remove uk-text-bold">Version</h4>
            <div><?php print $general_information['drupal']['version']; ?></div>
            <h4 class="uk-margin-small-top uk-margin-bottom-remove uk-text-bold">Installation Profile</h4>
            <div><?php print $general_information['drupal']['install_profile']; ?></div>
          </div>
        </div>

        <div class="uk-width-small-1-1 uk-width-medium-1-3">
          <i class="uk-icon-clock-o uk-icon-large uk-text-muted uk-width-1-5 uk-width-medium-1-10 uk-float-left uk-admin-vertical-align-top"></i>
          <div class="uk-width-4-5 uk-width-medium-9-10 uk-float-left">
            <h3 class="uk-text-bold uk-margin-small-bottom">Last Cron Run</h3>
            <div class="uk-float-right"><?php print $general_information['cron']['run_cron']; ?></div>
            <div><?php print $general_information['cron']['last_run']; ?></div>
            <div>(<?php print $general_information['cron']['more_information']; ?>)</div>
          </div>
        </div>
      </div>

      <hr class="uk-grid-divider">

      <div class="uk-grid">
        <div class="uk-width-small-1-1 uk-width-medium-1-3 uk-margin-bottom">
          <i class="uk-icon-server uk-icon-large uk-text-muted uk-width-1-5 uk-width-medium-1-10 uk-float-left uk-admin-vertical-align-top"></i>
          <div class="uk-width-4-5 uk-width-medium-9-10 uk-float-left">
            <h3 class="uk-text-bold uk-margin-small-bottom">Web Server</h3>
            <div><?php print $general_information['web_server']['value']; ?></div>
          </div>
        </div>

        <div class="uk-width-small-1-1 uk-width-medium-1-3 uk-margin-bottom">
          <i class="icon-php-alt uk-icon-large uk-text-muted uk-width-1-5 uk-width-medium-1-10 uk-float-left uk-admin-vertical-align-top"></i>
          <div class="uk-width-4-5 uk-width-medium-9-10 uk-float-left">
            <h3 class="uk-text-bold uk-margin-small-bottom">PHP</h3>
            <h4 class="uk-margin-small-top uk-margin-bottom-remove uk-text-bold">Version</h4>
            <div><?php print $general_information['php']['version']; ?></div>
            <h4 class="uk-margin-small-top uk-margin-bottom-remove uk-text-bold">Memory Limit</h4>
            <div><?php print $general_information['php']['memory_limit']; ?></div>
          </div>
        </div>

        <div class="uk-width-small-1-1 uk-width-medium-1-3">
          <i class="uk-icon-database uk-icon-large uk-text-muted uk-width-1-5 uk-width-medium-1-10 uk-float-left uk-admin-vertical-align-top"></i>
          <div class="uk-width-4-5 uk-width-medium-9-10 uk-float-left">
            <h3 class="uk-text-bold uk-margin-small-bottom">Database</h3>
            <h4 class="uk-margin-small-top uk-margin-bottom-remove uk-text-bold">Version</h4>
            <div><?php print $general_information['database']['version']; ?></div>
            <h4 class="uk-margin-small-top uk-margin-bottom-remove uk-text-bold">System</h4>
            <div><?php print $general_information['database']['system']; ?></div>
          </div>
        </div>
      </div>

    </div>
  </div>
</div>

<?php if ($errors): ?>
  <div id="errors" class="uk-grid">
    <h2 class="uk-margin-bottom">Errors found</h2>
    <div class="uk-width-1-1">
      <table id="system-status-errors" class="uk-table">
        <?php foreach ($grouped_requirements['error'] as $requirement): ?>
          <tr>
            <td class="system-status-title uk-text-danger uk-text-uppercase uk-width-small-1-2 uk-width-medium-1-4">
              <i class="uk-icon-exclamation-circle uk-icon-small uk-text-danger uk-margin-right"></i>
              <span class="uk-text-bold"><?php print $requirement['title']; ?></span>
            </td>
            <td class="system-status-error-description uk-width-small-1-2 uk-width-medium-3-4">
              <div class="system-status-value uk-text-danger"><?php print $requirement['value']; ?></div>
              <?php if (!empty($requirement['description'])): ?>
                <div class="system-status-description uk-text-muted"><?php print $requirement['description']; ?></div>
              <?php endif; ?>
            </td>
          </tr>
        <?php endforeach; ?>
      </table>
    </div>
  </div>
<?php endif; ?>

<?php if ($warnings): ?>
  <div id="warnings" class="uk-grid">
    <h2 class="uk-margin-bottom">Warnings found</h2>
    <div class="uk-width-1-1">
      <table id="system-status-warnings" class="uk-table">
        <?php foreach ($grouped_requirements['warning'] as $requirement): ?>
          <tr>
            <td class="system-status-title uk-text-warning uk-text-uppercase uk-width-small-1-2 uk-width-medium-1-4">
              <i class="uk-icon-exclamation-triangle uk-icon-small uk-text-warning uk-margin-right"></i>
              <span class="uk-text-bold"><?php print $requirement['title']; ?></span>
            </td>
            <td class="system-status-warning-description uk-width-small-1-2 uk-width-medium-3-4">
              <div class="system-status-value uk-text-warning"><?php print $requirement['value']; ?></div>
              <?php if (!empty($requirement['description'])): ?>
                <div class="system-status-description uk-text-muted"><?php print $requirement['description']; ?></div>
              <?php endif; ?>
            </td>
          </tr>
        <?php endforeach; ?>
      </table>
    </div>
  </div>
<?php endif; ?>

<div id="checked" class="uk-grid">
  <h2 class="uk-margin-bottom">Checked</h2>
  <div class="uk-width-1-1">
    <table id="system-status-checked" class="uk-table">
      <?php foreach ($requirements as $requirement): ?>
        <?php $severity = isset($requirement['severity']) ? $requirement['severity'] : 0; ?>
        <?php if ($severity == REQUIREMENT_INFO || $severity == REQUIREMENT_WARNING): ?>
          <?php $cell_class = 'uk-admin-status-padding-icon'; ?>
        <?php else: ?>
          <?php $cell_class = 'uk-admin-status-padding-normal'; ?>
        <?php endif; ?>
        <tr>
          <td class="system-status-title uk-text-uppercase uk-width-small-1-2 uk-width-medium-1-4 <?php print $cell_class; ?>">
            <?php if ($severity == REQUIREMENT_INFO): ?>
              <i class="uk-icon-info-circle uk-text-primary uk-icon-small uk-text-info uk-margin-right"></i>
              <span class="uk-text-bold uk-text-primary"><?php print $requirement['title']; ?></span>
            <?php elseif ($severity == REQUIREMENT_WARNING): ?>
              <i class="uk-icon-exclamation-triangle uk-text-warning uk-icon-small uk-text-info uk-margin-right"></i>
              <span class="uk-text-bold uk-text-warning"><?php print $requirement['title']; ?></span>
            <?php else: ?>
              <span class="uk-text-bold"><?php print $requirement['title']; ?></span>
            <?php endif; ?>
          </td>
          <td class="system-status-description uk-width-small-1-2 uk-width-medium-3-4">
            <?php if ($severity == REQUIREMENT_INFO): ?>
              <div class="system-status-value uk-text-primary"><?php print $requirement['value']; ?></div>
            <?php elseif ($severity == REQUIREMENT_WARNING): ?>
              <div class="system-status-value uk-text-warning"><?php print $requirement['value']; ?></div>
            <?php else: ?>
              <div class="system-status-value"><?php print $requirement['value']; ?></div>
            <?php endif; ?>
            <?php if (!empty($requirement['description'])): ?>
              <div class="system-status-description uk-text-muted"><?php print $requirement['description']; ?></div>
            <?php endif; ?>
          </td>
        </tr>
      <?php endforeach; ?>
    </table>
  </div>
</div>
