/**
 * @file
 * Attaches behaviors for Drupal core resizable textareas.
 */
(function ($) {

Drupal.behaviors.textarea = {
  attach: function (context, settings) {
    $('.form-textarea-wrapper.resizable', context).once('textarea', function () {
      $(this).parent().addClass('form-item-textarea-resizeable');
      var staticOffset = null;
      var textarea = $(this).addClass('resizable-textarea').find('textarea');
      var panel = $(this).parent().next().attr('id');
      var grippie = $('<div class="grippie uk-text-center"><i class="uk-icon-bars"></i></div>').mousedown(startDrag);

      grippie.insertAfter(textarea);

      function startDrag(e) {
        staticOffset = textarea.height() - e.pageY;
        textarea.css('opacity', 0.7);
        grippie.css('opacity', 0.7);
        $('#' + panel).css('opacity', 0.7);
        $(document).mousemove(performDrag).mouseup(endDrag);
        return false;
      }

      function performDrag(e) {
        textarea.height(Math.max(32, staticOffset + e.pageY) + 'px');
        return false;
      }

      function endDrag(e) {
        $(document).unbind('mousemove', performDrag).unbind('mouseup', endDrag);
        textarea.css('opacity', 1);
        grippie.css('opacity', 1);
        $('#' + panel).css('opacity', 1);
      }
    });
  }
};

})(jQuery);
