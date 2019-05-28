void console_trace_putc(const char *str)
{
  /* mask intr*/
  unsigned int intr_state = task_mask_exceptions(TASK_EXCEPTIONS_ALL);
  
  /* recovery */
  task_unmask_exceptions(intr_state);
}
